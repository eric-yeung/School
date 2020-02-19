from mininglibrary import MiningLibrary

fileName = "retail.txt"
support = 1000

counter = {}

counter, buckets, all_pairs = MiningLibrary.read_and_hash(counter, fileName)
counter = MiningLibrary.validate_support(counter, support)
bitmap = MiningLibrary.get_bitmap(buckets, support)

frequent_pairs = []

# Check frequent pairs against bitmap
for pair in all_pairs:
  hashVal = hash(pair)
  
  if MiningLibrary.validate_pair(counter, bitmap, pair):
    frequent_pairs.append(pair)

print(frequent_pairs, len(frequent_pairs))
