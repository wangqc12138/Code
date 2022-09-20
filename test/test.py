from collections import defaultdict
def tree(): return defaultdict(tree)


recursive_dict = tree()
recursive_dict['age'] = 2016
print(recursive_dict)
recursive_dict['bob']['age'] = 2
print(recursive_dict)
recursive_dict['charlie']['food']['dessert'] = 222
print(recursive_dict)
