import lief
import sys

if len(sys.argv)<3:
    exit()

with open(sys.argv[1], "rb") as f:
    body = f.read()

elfPath = sys.argv[2]

arr = []
for i  in body:
    arr.append(int(i))

binary = lief.parse(elfPath)

segment = lief.ELF.Segment()
segment.type = lief.ELF.SEGMENT_TYPES.LOAD
segment.content = arr
segment.flags = lief.ELF.SEGMENT_FLAGS(1)
segment = binary.replace(segment, binary[lief.ELF.SEGMENT_TYPES.NOTE])

binary.write(sys.argv[3])