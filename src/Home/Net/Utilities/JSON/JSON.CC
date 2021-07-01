#define JSONT_INVALID	0
#define JSONT_STRING	1
#define JSONT_INTEGER	2
#define JSONT_FLOAT		3
#define JSONT_ARRAY		4
#define JSONT_BOOL		5
#define JSONT_OBJ		6
#define JSONT_NULL		7

#define JSON_HASHTABLE_SIZE	1024

#define HTT_JSON	0x00100 //identical to HTT_DICT_WORD

class CJSONDataEntry:CQueue
{
	U8		 		 type;

	I64				 int_data;
	F64				 float_data;
	U8				*string_data;
	Bool			 bool_data;
	CJSONDataEntry	*list_data;
	CHashTable		*hash_table;
};

class CJSONDataHash:CHash
{
	CJSONDataEntry	*data;
};

U8 **JSONGetKeys(CHashTable *table)
{
	I64		  i, count = 0;
	CHash	 *temp_hash;
	U8		**keys;
	I64		  key_index = 0;

	for (i = 0; i <= table->mask; i++) //mask is table length 0-based
		if (temp_hash = table->body[i]) //if temp_hash exists
			count++;

	keys = CAlloc(sizeof(U8*) * count); // alloc string list
	for (i = 0; i <= table->mask; i++)
		if (temp_hash = table->body[i])
		{
			keys[key_index] = StrNew(temp_hash->str);//add key string to list
			key_index++;
		}

	return keys;
}

U0 JSONIndentLine(I64 indent)
{
	I64 i;
//	for (i = 0; i < indent; i++) {"  ";}
	for (i = 0; i < indent; i++) {"	";}

}

U0 JSONDataRep(CJSONDataEntry *data, I64 indent=0)
{
	U8				**keys;// = JSONGetKeys(data->hash_table);
	I64				  index;
	I64				  count;// = MSize(keys) / sizeof(U8*);
	CJSONDataEntry	 *entry;// = data->list_data->next;//one after head.
	CJSONDataHash	 *temp_hash;

	JSONIndentLine(indent);

	switch (data->type)
	{
		case JSONT_INVALID:
			"Invalid JSON.\n";
			break;

		case JSONT_STRING:
			"%s\n", data->string_data;
			break;

		case JSONT_INTEGER:
			"%d\n", data->int_data;
			break;

		case JSONT_FLOAT:
			"%.9f\n", data->float_data;
			break;

		case JSONT_BOOL:
			"%Z\n", data->bool_data, "ST_FALSE_TRUE";
			break;

		case JSONT_NULL:
			"Null.\n";
			break;

		case JSONT_ARRAY:
			"Array:\n";
			JSONIndentLine(indent);
			"[\n";
			entry = data->list_data->next;//one after head.
			while (entry != data->list_data)//head ignored, stop on head.
			{
				JSONDataRep(entry, indent + 1); // recursive Rep on the list entry
				entry = entry->next;
			}
			JSONIndentLine(indent);
			"]\n";
			break;

		case JSONT_OBJ:
			"Object.\n";
			JSONIndentLine(indent);
			"{\n";

			keys = JSONGetKeys(data->hash_table);
			count = MSize(keys) / sizeof(U8*);

			for (index = 0; index < count; index++)
			{
				JSONIndentLine(indent);
				"Key: %s\n", keys[index];
				temp_hash = HashFind(keys[index], data->hash_table, HTT_JSON);
				JSONDataRep(temp_hash->data, indent + 1);
			}
			JSONIndentLine(indent);
			"}\n";
			break;
	}
}

CJSONDataEntry *JSONParse(CCompCtrl *cc)
{
	CJSONDataEntry	*result = CAlloc(sizeof(CJSONDataEntry));
	I64				 tk, last_tk;
	Bool			 is_done = FALSE;
	CJSONDataEntry	*temp_entry;// = JSONParse(cc);
	CJSONDataHash	*temp_hash = CAlloc(sizeof(CJSONDataHash));

	while (tk = Lex(cc))
	{
//		ClassRep(cc);
		switch (tk)
		{

			case '}':
				LexExcept(cc, "Expected Value, got '}'.");
			case TK_STR:
				result->type		= JSONT_STRING;
				result->string_data = StrNew(cc->cur_str);

				is_done = TRUE;
				break;

			case TK_I64: //todo, LexExcept on 0x or 0b vals.
				result->type	 = JSONT_INTEGER;
				result->int_data = cc->cur_i64;

//				LexPush(cc);
//				"got hex val, token string is %s\n",cc->cur_str;
//				ClassRep(cc);
//				Break;

				is_done = TRUE;
				break;

			case TK_F64:
				result->type		= JSONT_FLOAT;
				result->float_data	= cc->cur_f64;

				is_done = TRUE;
				break;

			case TK_IDENT:
				if (!StrCompare(cc->cur_str, "true") ||
					!StrCompare(cc->cur_str, "false"))
				{
					result->type = JSONT_BOOL;

					if (!StrCompare(cc->cur_str, "true"))
						result->bool_data = TRUE;
					if (!StrCompare(cc->cur_str, "false"))
						result->bool_data = FALSE;

					is_done = TRUE;
				}
				if (!StrCompare(cc->cur_str, "null"))
				{
					result->type = JSONT_NULL;

					is_done = TRUE;
				}

				is_done = TRUE;
				break;

			case '[':
				result->type	  = JSONT_ARRAY;
				result->list_data = CAlloc(sizeof(CJSONDataEntry));
				QueueInit(result->list_data);

lex_listitem:
/*
				CCompCtrl* temp_cc = NULL;
				MemCopy(temp_cc, cc, CompCtrlSize(cc));
				tk = Lex(temp_cc);
//				CompCtrlDel(temp_cc);
*/
				last_tk = tk;
				LexPush(cc);
				tk = Lex(cc);

				if (last_tk == ',' && tk == ']')
					LexExcept(cc, "Expected List value, got ']'");

				if (tk == ']')
					goto lex_listdone;

				if (tk == ',')
					LexExcept(cc, "Expected List Value, got comma.");

				LexPopRestore(cc);
				temp_entry = JSONParse(cc);
				QueueInsert(temp_entry, result->list_data->last);

				tk = Lex(cc);
				if (tk == ',')
					goto lex_listitem;

lex_listdone:

//				LexPopNoRestore(cc);
				is_done = TRUE;
				break;

			case '{':
				result->type		= JSONT_OBJ;
				result->hash_table	= HashTableNew(JSON_HASHTABLE_SIZE);

lex_objkey:
				//lex next. expect TK_STR. Make a temp_hash.
				last_tk = tk;
				tk = Lex(cc);

				if (last_tk == ',' && tk == '}')
					LexExcept(cc, "Expected Key after comma.");

				if (tk == '}')
					goto lex_objdone;

				if (tk != TK_STR)
					LexExcept(cc, "Expected Key String.");

				temp_hash = CAlloc(sizeof(CJSONDataHash));

				//set hash type and StrNew with cc->cur_str into hash str.
				temp_hash->type = HTT_JSON;
				temp_hash->str  = StrNew(cc->cur_str);

				//lex next. expect ':'. 
				tk = Lex(cc);
				if (tk != ':')
					LexExcept(cc, "Expected ':' after Key String.");

				//now expect JSONDataEntry-able value next.
				//Recursive JSONParse into hash data member.
				temp_hash->data = JSONParse(cc);

				//JSONParse leaves off on the last token. e.g. int, tk will
				//still be TK_I64.

				//add hash to result hash_table.
				HashAdd(temp_hash, result->hash_table);
//				"Debugging.\nHash added with str:%s.\n",temp_hash->str;
//				ClassRep(temp_hash->data);

				//lex next. expect ',' or '}'.
				tk = Lex(cc);
				if (tk != ',' && tk != '}')
					LexExcept(cc, "Expected ',' or '}' after Object Value.");
				//if ',' ... Terry's parsing code would imply labels and gotos.
				//i wonder if there's a better, less BASIC way.
				if (tk == ',')
					goto lex_objkey;
lex_objdone:

				is_done = TRUE;
				break;
		}

		if (is_done)
			break;
	}

	return result;
}

U0 Test(U8 *filename)
{
	CCompCtrl		*cc		= CompCtrlNew(MStrPrint("#include \"%s\"", filename));
	CJSONDataEntry	*result	= JSONParse(cc);

	JSONDataRep(result);
}

Cd(__DIR__);
Test("JSON1.TXT");