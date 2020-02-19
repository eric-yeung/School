from mininglibrary import MiningLibrary

filename = "retail.txt"
support = 1000

counter = {}
double_counter = {}

counter, n, line_set = MiningLibrary.read_and_count(counter, filename)
counter = MiningLibrary.validate_support(counter, support)

double_counter = MiningLibrary.count_double(counter, double_counter, line_set)
double_counter = MiningLibrary.validate_support(double_counter, support)

print(double_counter.keys(), len(double_counter.keys()))
