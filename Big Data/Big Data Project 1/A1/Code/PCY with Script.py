from mininglibrary import MiningLibrary
import time

fileName = "retail.txt"
# support = 1000

total_lines = 88163

chunks_for_dataset= [.01, .1, .2, .3, .4 ,.5, .6, .7, .8 , .9, 1]
support_threshold = [.01, .05, .1] 

counter = {}

print("Chunk Support Time")

for support in support_threshold: #for going through the support thresholds 
    for chunk in chunks_for_dataset: #checking data chunk percentages
      start = time.time() #starting a timer for the operation

      counter, buckets, all_pairs = MiningLibrary.read_and_hash(counter, fileName, int(chunk * total_lines))
      
      chunks_of_dataset = chunk * total_lines #need to calculate how many baskets are there
      threshold = support * chunks_of_dataset
    
      counter = MiningLibrary.validate_support(counter, chunks_of_dataset)
      bitmap = MiningLibrary.get_bitmap(buckets, chunks_of_dataset)

      frequent_pairs = []

      # Check frequent pairs against bitmap
      for pair in all_pairs:
        hashVal = hash(pair)
        
        if MiningLibrary.validate_pair(counter, bitmap, pair):
          frequent_pairs.append(pair)
      end = time.time()
      
      time_taken = (end - start) *1000  
      # print(chunk*100,"%",support*100,"%",time_taken)
      print(time_taken)

# print(frequent_pairs, len(frequent_pairs))
