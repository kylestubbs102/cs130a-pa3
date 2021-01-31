# cs130a-pa3

This program implements an altered version of an AVL and 2-4 tree. I implemented an AVL with a maximum height difference of 2 and a 2-5 tree.

For each tree, I implemented the functions to search for a word, insert a word, and do a range search to print out all the words between the given boundaries.

In order to run the program, it is required to put PA3_dataset.txt after the executable, and put the commands in a string separated by commas. An example command would look like "search dog, insert cat, range search cat to dog"

All together, the command would look like:
./prog1.out PA3_dataset.txt "search dog, insert cat, range search cat to dog"

This would insert all of the data from the .txt file into both trees, and each following command executes and creates a separate print statement.
