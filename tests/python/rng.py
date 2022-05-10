
splitmix_state = 0
lfsr = 0x6e789e6aa1b965f4e220a8397b1dcdaf

UINT64MAX = (1<<64) - 1
UINT128MAX = (1<<128) - 1

def splitmix64() -> int:
	global splitmix_state
	splitmix_state = (splitmix_state + 0x9E3779B97f4A7C15) & UINT64MAX
	result = splitmix_state
	result = ((result ^ (result >> 30)) * 0xBF58476D1CE4E5B9) & UINT64MAX
	result = ((result ^ (result >> 27)) * 0x94D049BB133111EB) & UINT64MAX
	return result ^ (result >> 31)

def lfsr_next():
	global lfsr
	out = lfsr & 1
	fbk = (lfsr ^ (lfsr>>1) ^ (lfsr>>2) ^ (lfsr>>7)) & 1
	lfsr = ((lfsr>>1) | (fbk << 127)) & UINT128MAX
	return out


if __name__ == '__main__':
	bits = [lfsr_next() for _ in range(256)]
	print(bits)