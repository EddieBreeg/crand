
splitmix_state = 0
lfsr = 0x6e789e6aa1b965f4e220a8397b1dcdaf
xoshiro_state: list

UINT64MAX = (1<<64) - 1
UINT32MAX = (1<<32) - 1
UINT128MAX = (1<<128) - 1

def rotl64(x: int, k: int) -> int:
	return ((x << k) & UINT64MAX) | (x >> (64-k))

def splitmix64() -> int:
	global splitmix_state
	splitmix_state = (splitmix_state + 0x9E3779B97f4A7C15) & UINT64MAX
	result = splitmix_state
	result = ((result ^ (result >> 30)) * 0xBF58476D1CE4E5B9) & UINT64MAX
	result = ((result ^ (result >> 27)) * 0x94D049BB133111EB) & UINT64MAX
	return result ^ (result >> 31)

def xoshiro_next():
	global xoshiro_state
	t = (xoshiro_state[1] << 17) & UINT64MAX

	xoshiro_state[2] ^= xoshiro_state[0]
	xoshiro_state[3] ^= xoshiro_state[1]
	xoshiro_state[1] ^= xoshiro_state[2]
	xoshiro_state[0] ^= xoshiro_state[3]

	xoshiro_state[2] ^= t

	xoshiro_state[3] = rotl64(xoshiro_state[3], 45)
	return t


def xorshift32(x):
	x = (x ^ (x << 13)) & UINT32MAX
	x = (x ^ (x >> 17)) & UINT32MAX
	return ((x ^ (x << 5)) & UINT32MAX)

def xorshift64(x):
	x = x ^ (x << 13) & UINT64MAX
	x = x ^ (x >> 7) & UINT64MAX
	return (x ^ (x << 17)) & UINT64MAX

def lfsr_next():
	global lfsr
	out = lfsr & 1
	fbk = (lfsr ^ (lfsr>>1) ^ (lfsr>>2) ^ (lfsr>>7)) & 1
	lfsr = ((lfsr>>1) | (fbk << 127)) & UINT128MAX
	return out


if __name__ == '__main__':
	xoshiro_state = [splitmix64(), splitmix64(), splitmix64(), splitmix64()]
	for _ in range(8):
		print(hex(xoshiro_next()))