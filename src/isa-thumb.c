#include "isa-thumb.h"

static const ThumbInstruction _thumbTable[0x400];

// Instruction definitions
// Beware pre-processor insanity

#define APPLY(F, ...) F(__VA_ARGS__)

#define COUNT_1(EMITTER, PREFIX, ...) \
	EMITTER(PREFIX ## 0, 0, __VA_ARGS__) \
	EMITTER(PREFIX ## 1, 1, __VA_ARGS__)

#define COUNT_2(EMITTER, PREFIX, ...) \
	COUNT_1(EMITTER, PREFIX, __VA_ARGS__) \
	EMITTER(PREFIX ## 2, 2, __VA_ARGS__) \
	EMITTER(PREFIX ## 3, 3, __VA_ARGS__)

#define COUNT_3(EMITTER, PREFIX, ...) \
	COUNT_2(EMITTER, PREFIX, __VA_ARGS__) \
	EMITTER(PREFIX ## 4, 4, __VA_ARGS__) \
	EMITTER(PREFIX ## 5, 5, __VA_ARGS__) \
	EMITTER(PREFIX ## 6, 6, __VA_ARGS__) \
	EMITTER(PREFIX ## 7, 7, __VA_ARGS__)

#define COUNT_4(EMITTER, PREFIX, ...) \
	COUNT_3(EMITTER, PREFIX, __VA_ARGS__) \
	EMITTER(PREFIX ## 8, 8, __VA_ARGS__) \
	EMITTER(PREFIX ## 9, 9, __VA_ARGS__) \
	EMITTER(PREFIX ## A, 10, __VA_ARGS__) \
	EMITTER(PREFIX ## B, 11, __VA_ARGS__) \
	EMITTER(PREFIX ## C, 12, __VA_ARGS__) \
	EMITTER(PREFIX ## D, 13, __VA_ARGS__) \
	EMITTER(PREFIX ## E, 14, __VA_ARGS__) \
	EMITTER(PREFIX ## F, 15, __VA_ARGS__)

#define COUNT_5(EMITTER, PREFIX, ...) \
	COUNT_4(EMITTER, PREFIX ## 0, __VA_ARGS__) \
	EMITTER(PREFIX ## 10, 16, __VA_ARGS__) \
	EMITTER(PREFIX ## 11, 17, __VA_ARGS__) \
	EMITTER(PREFIX ## 12, 18, __VA_ARGS__) \
	EMITTER(PREFIX ## 13, 19, __VA_ARGS__) \
	EMITTER(PREFIX ## 14, 20, __VA_ARGS__) \
	EMITTER(PREFIX ## 15, 21, __VA_ARGS__) \
	EMITTER(PREFIX ## 16, 22, __VA_ARGS__) \
	EMITTER(PREFIX ## 17, 23, __VA_ARGS__) \
	EMITTER(PREFIX ## 18, 24, __VA_ARGS__) \
	EMITTER(PREFIX ## 19, 25, __VA_ARGS__) \
	EMITTER(PREFIX ## 1A, 26, __VA_ARGS__) \
	EMITTER(PREFIX ## 1B, 27, __VA_ARGS__) \
	EMITTER(PREFIX ## 1C, 28, __VA_ARGS__) \
	EMITTER(PREFIX ## 1D, 29, __VA_ARGS__) \
	EMITTER(PREFIX ## 1E, 30, __VA_ARGS__) \
	EMITTER(PREFIX ## 1F, 31, __VA_ARGS__) \

#define THUMB_WRITE_PC \
	cpu->gprs[ARM_PC] = (cpu->gprs[ARM_PC] & -WORD_SIZE_THUMB) + WORD_SIZE_THUMB

#define DEFINE_INSTRUCTION_THUMB(NAME, BODY) \
	static void _ThumbInstruction ## NAME (struct ARMCore* cpu, uint16_t opcode) {  \
		BODY; \
	}

#define DEFINE_SHIFT_1_INSTRUCTION_EX_THUMB(NAME, IMMEDIATE, BODY) \
	DEFINE_INSTRUCTION_THUMB(NAME, \
		int immediate = IMMEDIATE; \
		BODY;)

#define DEFINE_SHIFT_1_INSTRUCTION_THUMB(NAME, BODY) \
	COUNT_5(DEFINE_SHIFT_1_INSTRUCTION_EX_THUMB, NAME ## 1_, BODY)

DEFINE_SHIFT_1_INSTRUCTION_THUMB(LSL, )
DEFINE_SHIFT_1_INSTRUCTION_THUMB(LSR, )
DEFINE_SHIFT_1_INSTRUCTION_THUMB(ASR, )

#define DEFINE_DATA_FORM_1_INSTRUCTION_EX_THUMB(NAME, RM, BODY) \
	DEFINE_INSTRUCTION_THUMB(NAME, \
		int rm = RM; \
		BODY;)

#define DEFINE_DATA_FORM_1_INSTRUCTION_THUMB(NAME, BODY) \
	COUNT_3(DEFINE_DATA_FORM_1_INSTRUCTION_EX_THUMB, NAME ## 3_R, BODY)

DEFINE_DATA_FORM_1_INSTRUCTION_THUMB(ADD, )
DEFINE_DATA_FORM_1_INSTRUCTION_THUMB(SUB, )

#define DEFINE_DATA_FORM_2_INSTRUCTION_EX_THUMB(NAME, IMMEDIATE, BODY) \
	DEFINE_INSTRUCTION_THUMB(NAME, \
		int immediate = IMMEDIATE; \
		BODY;)

#define DEFINE_DATA_FORM_2_INSTRUCTION_THUMB(NAME, BODY) \
	COUNT_3(DEFINE_DATA_FORM_2_INSTRUCTION_EX_THUMB, NAME ## 1_, BODY)

DEFINE_DATA_FORM_2_INSTRUCTION_THUMB(ADD, )
DEFINE_DATA_FORM_2_INSTRUCTION_THUMB(SUB, )

#define DEFINE_DATA_FORM_3_INSTRUCTION_EX_THUMB(NAME, RD, BODY) \
	DEFINE_INSTRUCTION_THUMB(NAME, \
		int rd = RD; \
		BODY;)

#define DEFINE_DATA_FORM_3_INSTRUCTION_THUMB(NAME, BODY) \
	COUNT_3(DEFINE_DATA_FORM_3_INSTRUCTION_EX_THUMB, NAME ## _R, BODY)

DEFINE_DATA_FORM_3_INSTRUCTION_THUMB(ADD2, )
DEFINE_DATA_FORM_3_INSTRUCTION_THUMB(CMP1, )
DEFINE_DATA_FORM_3_INSTRUCTION_THUMB(MOV1, )
DEFINE_DATA_FORM_3_INSTRUCTION_THUMB(SUB2, )

#define DEFINE_DATA_FORM_5_INSTRUCTION_THUMB(NAME, BODY) \
	DEFINE_INSTRUCTION_THUMB(NAME, \
		int rd = opcode & 0x0007; \
		int rn = (opcode >> 3) & 0x0007; \
		BODY;)

DEFINE_DATA_FORM_5_INSTRUCTION_THUMB(AND, )
DEFINE_DATA_FORM_5_INSTRUCTION_THUMB(EOR, )
DEFINE_DATA_FORM_5_INSTRUCTION_THUMB(LSL2, )
DEFINE_DATA_FORM_5_INSTRUCTION_THUMB(LSR2, )
DEFINE_DATA_FORM_5_INSTRUCTION_THUMB(ASR2, )
DEFINE_DATA_FORM_5_INSTRUCTION_THUMB(ADC, )
DEFINE_DATA_FORM_5_INSTRUCTION_THUMB(SBC, )
DEFINE_DATA_FORM_5_INSTRUCTION_THUMB(ROR, )
DEFINE_DATA_FORM_5_INSTRUCTION_THUMB(TST, )
DEFINE_DATA_FORM_5_INSTRUCTION_THUMB(NEG, )
DEFINE_DATA_FORM_5_INSTRUCTION_THUMB(CMP2, )
DEFINE_DATA_FORM_5_INSTRUCTION_THUMB(CMN, )
DEFINE_DATA_FORM_5_INSTRUCTION_THUMB(ORR, )
DEFINE_DATA_FORM_5_INSTRUCTION_THUMB(MUL, )
DEFINE_DATA_FORM_5_INSTRUCTION_THUMB(BIC, )
DEFINE_DATA_FORM_5_INSTRUCTION_THUMB(MVN, )

#define DEFINE_INSTRUCTION_WITH_HIGH_EX_THUMB(NAME, H1, H2, BODY) \
	DEFINE_INSTRUCTION_THUMB(NAME, \
		int rd = opcode & 0x0007 | H1; \
		int rm = (opcode >> 3) & 0x0007 | H2; \
		BODY;)

#define DEFINE_INSTRUCTION_WITH_HIGH_THUMB(NAME, BODY) \
	DEFINE_INSTRUCTION_WITH_HIGH_EX_THUMB(NAME ## 00, 0, 0, BODY) \
	DEFINE_INSTRUCTION_WITH_HIGH_EX_THUMB(NAME ## 01, 0, 8, BODY) \
	DEFINE_INSTRUCTION_WITH_HIGH_EX_THUMB(NAME ## 10, 8, 0, BODY) \
	DEFINE_INSTRUCTION_WITH_HIGH_EX_THUMB(NAME ## 11, 8, 8, BODY)

DEFINE_INSTRUCTION_WITH_HIGH_THUMB(ADD4, )
DEFINE_INSTRUCTION_WITH_HIGH_THUMB(CMP3, )
DEFINE_INSTRUCTION_WITH_HIGH_THUMB(MOV3, )

DEFINE_INSTRUCTION_THUMB(ILL, )

#define DECLARE_INSTRUCTION_THUMB(EMITTER, NAME) \
	EMITTER ## NAME

#define DECLARE_INSTRUCTION_WITH_HIGH_THUMB(EMITTER, NAME) \
	DECLARE_INSTRUCTION_THUMB(EMITTER, NAME ## 00), \
	DECLARE_INSTRUCTION_THUMB(EMITTER, NAME ## 01), \
	DECLARE_INSTRUCTION_THUMB(EMITTER, NAME ## 10), \
	DECLARE_INSTRUCTION_THUMB(EMITTER, NAME ## 11)

#define DUMMY(X, ...) X,
#define DUMMY_4(...) \
	DUMMY(__VA_ARGS__) \
	DUMMY(__VA_ARGS__) \
	DUMMY(__VA_ARGS__) \
	DUMMY(__VA_ARGS__)

#define DECLARE_THUMB_EMITTER_BLOCK(EMITTER) \
	APPLY(COUNT_5, DUMMY, DECLARE_INSTRUCTION_THUMB(EMITTER, LSL1_)) \
	APPLY(COUNT_5, DUMMY, DECLARE_INSTRUCTION_THUMB(EMITTER, LSR1_)) \
	APPLY(COUNT_5, DUMMY, DECLARE_INSTRUCTION_THUMB(EMITTER, ASR1_)) \
	APPLY(COUNT_3, DUMMY, DECLARE_INSTRUCTION_THUMB(EMITTER, ADD3_R)) \
	APPLY(COUNT_3, DUMMY, DECLARE_INSTRUCTION_THUMB(EMITTER, SUB3_R)) \
	APPLY(COUNT_3, DUMMY, DECLARE_INSTRUCTION_THUMB(EMITTER, ADD1_)) \
	APPLY(COUNT_3, DUMMY, DECLARE_INSTRUCTION_THUMB(EMITTER, SUB1_)) \
	APPLY(COUNT_3, DUMMY_4, DECLARE_INSTRUCTION_THUMB(EMITTER, MOV1_R)) \
	APPLY(COUNT_3, DUMMY_4, DECLARE_INSTRUCTION_THUMB(EMITTER, CMP1_R)) \
	APPLY(COUNT_3, DUMMY_4, DECLARE_INSTRUCTION_THUMB(EMITTER, ADD2_R)) \
	APPLY(COUNT_3, DUMMY_4, DECLARE_INSTRUCTION_THUMB(EMITTER, SUB2_R)) \
	DECLARE_INSTRUCTION_THUMB(EMITTER, AND), \
	DECLARE_INSTRUCTION_THUMB(EMITTER, EOR), \
	DECLARE_INSTRUCTION_THUMB(EMITTER, LSL2), \
	DECLARE_INSTRUCTION_THUMB(EMITTER, LSR2), \
	DECLARE_INSTRUCTION_THUMB(EMITTER, ASR2), \
	DECLARE_INSTRUCTION_THUMB(EMITTER, ADC), \
	DECLARE_INSTRUCTION_THUMB(EMITTER, SBC), \
	DECLARE_INSTRUCTION_THUMB(EMITTER, ROR), \
	DECLARE_INSTRUCTION_THUMB(EMITTER, TST), \
	DECLARE_INSTRUCTION_THUMB(EMITTER, NEG), \
	DECLARE_INSTRUCTION_THUMB(EMITTER, CMP2), \
	DECLARE_INSTRUCTION_THUMB(EMITTER, CMN), \
	DECLARE_INSTRUCTION_THUMB(EMITTER, ORR), \
	DECLARE_INSTRUCTION_THUMB(EMITTER, MUL), \
	DECLARE_INSTRUCTION_THUMB(EMITTER, BIC), \
	DECLARE_INSTRUCTION_THUMB(EMITTER, MVN), \
	DECLARE_INSTRUCTION_WITH_HIGH_THUMB(EMITTER, ADD4), \
	DECLARE_INSTRUCTION_WITH_HIGH_THUMB(EMITTER, CMP3), \
	DECLARE_INSTRUCTION_WITH_HIGH_THUMB(EMITTER, MOV3), \
	DECLARE_INSTRUCTION_THUMB(EMITTER, ILL), \
	DECLARE_INSTRUCTION_THUMB(EMITTER, ILL), \
	DECLARE_INSTRUCTION_THUMB(EMITTER, ILL), \
	DECLARE_INSTRUCTION_THUMB(EMITTER, ILL), \
	DECLARE_INSTRUCTION_THUMB(EMITTER, ILL)

static const ThumbInstruction _thumbTable[0x400] = {
	DECLARE_THUMB_EMITTER_BLOCK(_ThumbInstruction)
};
