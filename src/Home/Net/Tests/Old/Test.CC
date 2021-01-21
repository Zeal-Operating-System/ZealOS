






//#define IP_PARSE_STATE_FIRST_NUM	0
#define IP_PARSE_STATE_NUM			1
#define IP_PARSE_STATE_DOT			2
#define IP_PARSE_STATE_ERROR		3


I64	IPV4AddressParse(U8 *string, U32 destination)
{//destination output in network order, only write on success

	I64 i;
	I64 parse_state = IP_PARSE_STATE_NUM;
	U32 temp_destination = 0;

	I64 current_chunk_index = 0;
	U8 *digit_buffer = StrNew("");
	
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