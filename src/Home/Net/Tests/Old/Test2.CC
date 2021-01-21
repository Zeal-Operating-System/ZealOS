






//#define IP_PARSE_STATE_FIRST_NUM	0
#define IP_PARSE_STATE_NUM			1
#define IP_PARSE_STATE_DOT			2
#define IP_PARSE_STATE_ERROR		3








/*

U8 *StrDotReplace(U8* source_string)
{
	I64 i;

	U8 *result = StrNew(source_string);

	for (i = 0; i < StrLen(result); i++)
	{
		if (result[i] == ',')
		{ // we're using commas internally for Lexing.
			result[i] = '.';
		} // so if we see a comma, set to dot, break lexer.
		else if (result[i] == '.')
		{ // Lex eats '.' as F64. Comma will split Lex tokens
			result[i] = ',';
		}
	}

	return result;
}
*/

Bool IPV4AddressParse(U8 *string, U32* destination)
{
//	U8* lexable_string;
//	lexable_string = StrReplace(string, ",", ","); // swap any commas with an unexpected value

	U8 *lexable_string = StrReplace(string, ".", ","); // swap dots with commas since Lex is easier with them.

	CCompCtrl* cc = CompCtrlNew(lexable_string);
	//Bts(&cc->opts, OPTf_DECIMAL_ONLY);

	cc->opts |= 1 << OPTf_DECIMAL_ONLY;

	I64 tk;

	I64 state = IP_PARSE_STATE_NUM;
	U32 temp_destination = 0;

	I64 current_section = 0; // IPV4 address has 4 total sections

	while (tk = Lex(cc))
	{
		switch (state)
		{
			case IP_PARSE_STATE_NUM:
				switch (tk)
				{
					case TK_I64:
						if (cc->cur_i64 > 255 || cc->cur_i64 < 0)
						{
							NetErr("Invalid value, must be 0 - 255.\n");
							return FALSE;
						}
						if (current_section > 3)
						{
							NetErr("IP Address can only have 4 sections.\n");
							return FALSE;
						}

						temp_destination |= cc->cur_i64 << (current_section * 8);
						current_section++;
						
						state = IP_PARSE_STATE_DOT;

						break;

					default:
						NetErr("Expected decimal. \n");
						return FALSE;
				}
				break;

			case IP_PARSE_STATE_DOT:
				switch (tk)
				{
					case ',':
						state = IP_PARSE_STATE_NUM;
						break;

					default:
						NetErr("Expected dot. \n");
						return FALSE;
				}
				break;
		}
	}

	temp_destination = EndianU32(temp_destination); // store the address in Network Byte Order (Big-Endian)
	*destination = temp_destination;
	"\n\n%X\n\n",temp_destination;
	return TRUE;
}
























I64	IPV4AddressParseOOOOOOOOOOPS(U8 *string, U32 destination)
{//destination output in network order, only write on success

	I64 i;
	I64 parse_state = IP_PARSE_STATE_NUM;
	U32 temp_destination = 0;

	I64 current_chunk_index = 0;
	U8 *digit_buffer = StrNew("");
	destination = 'nigggg';
	
	// chunk is just IPV4 num 0 through 3. on last chunk, don't go to DOT state.

	for (i = 0; i < 16; i++) //use the #define in Sockets
	{
		switch (parse_state)
		{
			case IP_PARSE_STATE_NUM:
				switch (string[i])
				{
					case '.':
						parse_state = IP_PARSE_STATE_DOT;
						break;

					case '0':
					case '1':
					case '2':
					case '3':
					case '4':
					case '5':
					case '6':
					case '7':
					case '8':
					case '9':
						StrPrint(digit_buffer, "%s%c", digit_buffer, string[i]);
						break;

					default:
						NetErr("IPV4 Parse Failure: Unexpected char.\n");
						parse_state = IP_PARSE_STATE_ERROR;
						break;


				}
				break;
			case IP_PARSE_STATE_DOT:
				"%s, %X\n", digit_buffer, Str2I64(digit_buffer);
				if (Str2I64(digit_buffer) > 255)
				{
					NetErr("IPV4 Parse Failure: Chunk exceeds 0 - 255 range.\n");
					parse_state = IP_PARSE_STATE_ERROR;
					break;
				}


				temp_destination |= Str2I64(digit_buffer) << (current_chunk_index * 8);

				StrCopy(digit_buffer, ""); // clear digit buffer


				current_chunk_index++;
				if (current_chunk_index > 3)
				{
					NetErr("IPV4 Parse Failure: Too many dots in address string.\n");
					parse_state = IP_PARSE_STATE_ERROR;
					break;
				}

				parse_state = IP_PARSE_STATE_NUM;

				break;

			case IP_PARSE_STATE_ERROR:
				NetErr("IPV4 Parse Failure: Invalid Address String.\n");
				return -1; // error state!
		}
	}

	return 0;


}