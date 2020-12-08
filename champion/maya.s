.name "MAYA"

.comment "Maya rah cha3b a cha3b"

start:
	live %5
	ld %640, r8
	st r1, -100
	st r8, -109
	st r15, 82
	fork %-500
	live %5
	ld %1, r2
	st r1, 100
	st r2, 91
	st r15, 82
	live %5
	fork %500
	live %5
	add r10, r11, r13
