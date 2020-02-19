from mininglibrary import MiningLibrary

import time

counter = {}
double_counter = {}
total_lines = 88163

chunks_for_dataset= [.01, .1, .2, .3, .4 ,.5, .6, .7, .8 , .9, 1]
support_threshold = [.01, .05, .1] 

print("Chunk Support Time")

for support in support_threshold: #for going through the support thresholds
    for chunk in chunks_for_dataset: #checking data chunk percentages
        start = time.time() #starting a timer for the operation

        counter, n, line_set = MiningLibrary.read_and_count(counter, "retail.txt", int(chunk * total_lines))
        
        chunks_of_dataset = chunk * total_lines
        threshold = support * chunks_of_dataset
        
        counter = MiningLibrary.validate_support(counter, chunks_of_dataset) #checking if the items are frequent or not

        double_counter = MiningLibrary.count_double(counter, double_counter, line_set) #checking if pairs are frequent
        double_counter = MiningLibrary.validate_support(double_counter, threshold)
		
        end = time.time()

        time_taken = (end - start) * 1000
        
        # print(chunk * 100,"%",support * 100,"%",time_taken)
        print(time_taken)