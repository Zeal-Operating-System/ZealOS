#help_index "God"

#define GOD_BAD_BITS	4
#define GOD_GOOD_BITS	24

public class CGodGlobals
{
	U8	**words,
		*word_file_mask;

	I64	word_fuf_flags,
		word_count;
	CFifoU8	*fifo;
} god;

MemSet(&god, 0, sizeof(CGodGlobals));
god.fifo = FifoU8New(2048 * 8);

extern U0 GodBiblePassage(I64 num_lines=20);
extern U0 GodBitsInsert(I64 num_bits, I64 bitfield);
extern U0 GodSong();
extern U0 GodWord(I64 bits=17);
