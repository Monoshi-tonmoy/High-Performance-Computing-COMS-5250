import random

def random_generated_list(size):
    lst = []
    for i in range(size):
        lst.append(random.randint(0,1000))
    return lst

def main():
    size = int(input("Please enter the size of the list:"))
    print("Here generating numbers in the range of 0-1000\n")

    lst = random_generated_list(size)

    print("\n.............Here is the randomly generated list................\n")
    print(lst)

    print("\n...............Use of append().................\n")
    lst.append(-100)
    print("The number -100 will be appended at the end of the list")
    print(f"Updated List after appending -100 {lst}\n")

    print("\n...........................Use of copy()......................\n")
    copied_lst = lst.copy()
    print(f"Original list lst:{lst}\ncopied list copied_lst{copied_lst}\n")

    print("\n.................Use of clear()...................\n")
    print(f"Before:{copied_lst}\n")
    copied_lst.clear()
    print(f"After:{copied_lst}\n")

    print("\n................Use of count()......................\n")
    freq = lst.count(-100)
    print(f"The occurence of -100 in the list is {freq}\n")

    print("\n..................Use of extend()....................\n")
    print("Extending [1,2,4] to the list:\n")
    lst.extend([1,2,4])
    print(f"Extended list: {lst}")

    print("\n............Use of index()...............\n")
    print("Find the index of element 2 in the list\n")
    idx = lst.index(2)
    print(f"The index of element 2 is {idx}\n")

    print("\n.................Use of insert()...................\n")
    print("Insert -100 at the 10th index of the list")
    lst.insert(10, -100)
    print(f"The list after inserting -100 is {lst}")

    print("\n...............Use of pop().........................\n")
    print("Pop the last element from the list")
    print(f"list before:{lst}\n")
    lst.pop()
    print(f"list after pop:{lst}\n")


    print("\n...........Use of remove()................\n")
    print("Remove the number 1 from the list")
    print(f"list before:{lst}\n")
    lst.remove(1)
    print(f"list after removing 1:{lst}\n")

    print("\n...........Use of reverse()................\n")
    print(f"list before:{lst}\n")
    lst.reverse()
    print(f"list after reversing:{lst}\n")

    print("\n............Use of sort()................\n")
    print(f"list before:{lst}\n")
    lst.sort()
    print(f"list after sorting:{lst}\n")


if __name__ == "__main__":
    main()