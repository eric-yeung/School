from itertools import combinations

class MiningLibrary:
  """Class containing library functions common to different
  mining algorithms, including A-Priori and PCY
  """

  def read_and_count(counter, filename, max_lines):
    """Read lines from the file specified and convert them to baskets.
    Read each item from the basket and update the counter for occurences.

    Args:
      counter (dict): has some item and the occurence as its value
      filename (str): the datafile to read and parse
      max_lines (int): max lines to read and count

    Returns:
      dict: dictionary that has all the items and their occurences
      int: number of baskets
      list: the list of baskets
    """
    # list and counter for baskets
    baskets = []
    n_baskets = 0
    # open file and read lines
    with open(filename) as fp:
      # loop through every line in file
      for line in fp:
        # break if reached % of file needed
        if n_baskets >= max_lines:
          break
        # remove trailing char and split by space to get list of numbers
        line = line.rstrip().split(" ")
        # create basket from line
        basket = MiningLibrary.basket_to_int(line)
        # add basket to list
        baskets.append(basket)
        # update counter occurence for count of single items
        counter = MiningLibrary.count_single(counter, basket)
        # increment counter
        n_baskets += 1
    # return the baskets and updated counter
    return (counter, n_baskets, baskets)


  def read_and_hash(counter, filename, max_lines):
    """Read lines from the file specified and convert them to baskets.
    Read each item from the basket and update the counter for occurences.
    Generate every pair from bucket and increment the buckets dictionary
    that counts the hashed pairs and the occurences.

    Args:
      counter (dict): has some item and the occurence as its value
      filename (str): the datafile to read and parse
      max_lines (int): max lines to read and count

    Returns:
      dict: dictionary that has all the items and their occurences
      list: the list of baskets
      dict: hashtable with pair hash and its occurences
    """
    buckets = {} # pair hashtable

    # set of all pairs and counter for baskets
    all_pairs = set()
    n_baskets = 0

    with open(filename) as fp:
      # loop through every line in file
      for line in fp:
        # break if reached % of file needed
        if n_baskets >= max_lines:
          break
        # remove trailing char and split by space to get list of numbers
        line = line.rstrip().split(" ")
        # create basket from line
        basket = MiningLibrary.basket_to_int(line)
        # update counter occurence for count of single items
        counter = MiningLibrary.count_single(counter, basket)
        # get all pairs from the basket
        pairs = MiningLibrary.get_pairs(basket)
        # count the pair hashes and store them into the hashtable, and store
        # pairs in a list
        buckets, all_pairs = MiningLibrary.count_hash(buckets, pairs, all_pairs)
        # increment counter
        n_baskets += 1
    # return all the datasets
    return counter, buckets, all_pairs


  def basket_to_int(basket):
    """Method converts an list of strings that contain 
    numbers to an list of ints by parsing each number.

    Args:
      basket (list of str): list of numbers represented as strings

    Returns:
      list of int: list numbers after being parsed

    """
    return [int(x) for x in basket]

  def get_pairs(frequents):
    """Method converts all the list of frequents into a list of tuple
    that has every combination of pairs using the numbers in that
    list that are unique and not duplicates (ex. not (1, 1)).

    Args:
      frequents (list of int): list of frequent numbers to be paired up

    Returns:
      list of (int, int): list of tuple containing pairs of ints
    """
    return list(combinations(frequents, 2))

  def validate_support(counter, support):
    """Method to check all the values in the counter dictionary
    and make sure it meets the support threshold. If it doesn't
    it removes it from the dictionary. In the end, it returns the
    new dictionary with values that all meet the support threshold.

    Args:
      counter (dict): has some item and the occurence as its value
      support (int): a minimum threshold of occurences it should meet

    Returns:
      dict: dictionary that has all the items that meet the support
    """
    # duplicate dictionary
    new_counter = counter.copy()
    # loop through every item
    for item in counter:
      # if the occurence doesnt meet the support, remove it
      if counter[item] < support:
        del new_counter[item]
    # return the new dictionary
    return new_counter
  
  def count_single(counter, basket):
    """Counts the occurence for each item in the basket and increments
    the counter in the counter dictionary

    Args:
      counter (dict): keeps track of the item number and its occurences
      basket (list of str): list of numbers as string to count

    Returns:
      dict: returns the counter with the updated occurences
    """
    # loop through every item in basket
    for item in basket:
      # if its already in the dict, increment it, otherwise add it with occurence 1
      if item in counter:
        counter[item] += 1
      else:
        counter[item] = 1
    # return updated dictionary
    return counter

  def count_double(frequent, counter, baskets):
    """Method to count the pairs in a basket that are also made up of
    frequent items. Only those pairs are counted.

    Args:
      frequent (dict): dictionary of frequent items
      counter (dict): dictionary to keep track of occurences of the pair
      baskets (list of list of int): contains all the baskets that are
      a list of items

    Returns:
      dict: updated dictionary with the occurences
    """
    # loop through every basket
    for basket in baskets:
      # generate list of candidate pairs from the basket
      basket_pairs = MiningLibrary.get_pairs(basket)
      # loop through all the pairs to check if they are made
      # up of frequent items
      for pair in basket_pairs:
        # check if both items in the pair are frequent
        if pair[0] in frequent and pair[1] in frequent:
          # increment pair counter, if it doesnt exist add it to counter
          if pair in counter:
            counter[pair] += 1
          else:
            counter[pair] = 1
      # return updated dictionary
    return counter

  def count_hash(buckets, pairs, all_pairs):
    """Counts the occurence for each pair hashed in a hashtable and
    keeps track of every unique pair in a set.

    Args:
      buckets (dict): hashtable to store occurences in
      pairs (list): list of pairs to hash and count
      all_pairs (set): set to store all unique pairs

    Returns:
      dict: updated hashtable with occurences
      set: updated set with pairs added
    """
    # loop through all the pairs
    for pair in pairs:
      # add pair to the set
      all_pairs.add(pair)
      # hash the pair to get its index in the hashtable
      index = hash(pair)
      # increment the occurence at the hash
      if index in buckets:
        buckets[index] = buckets[index] + 1
      else:
        buckets[index] = 1
    # return the hashtable and set of all pairs
    return buckets, all_pairs

  def get_bitmap(hashtable, support):
    """Creates a bitmap using the hashtable for all the
    hashes that meet the support threshold.

    Args:
      hashtable (dict): hashtable with occurences
      support (int): threshold to meet for occurences

    Returns:
      dict: bitmap with 1 representing hashes that meet support
    """
    # create new bitmap dict
    bitmap = {}
    # loop through every hash
    for hsh in hashtable:
      # if occurences meet support, set bit to 1 other wise 0
      if hashtable[hsh] < support:
        bitmap[hsh] = 0
      else:
        bitmap[hsh] = 1
    # return newly created bitmap
    return bitmap

  def validate_pair(counter, bitmap, pair):
    """Validates a pair to see if it is frequent or not by
    checking to see if it is in the bitmap and if it is
    made up of frequent items.

    Args:
      counter (dict): has some item and the occurence as its value
      bitmap (dict): bitmap with hashes and the bit representing 
      it meeting the support threshold or not (1 or 0)
      pair (tuple): the pair to validate

    Returns:
      bool: if the pair is frequent or not
    """
    # check if pair is frequent and if each item in pair is frequent
    return bitmap[hash(pair)] and pair[0] in counter and pair[1] in counter