The XML file is read block by block(i.e I am taking 12000 documents at a time and then creating the posting list of the words occurinng in those 12000 documents). The data structure used for creating the posting list is Trie.

I am using secondary index. The word and its posting list is written on a file whose path depends on the first two characters of the word. The code will create 26 *26 folders (from'aa' to 'zz') and each word will go in its respective folder. Inside each folder there are 6 files for each of the categories.

Now as the same word can occur in multiple blocks (block being 12000 documents being processed at one time) therefore each file will again need to be sorted. This can be done by using external merge sort or in memory sorting. As each of these files is small enough for in memory sorting I have applied that, and merged same word entries.

For each word I have calculated the offset(i.e number of bytes in the file after which it has it posting list). 

For each word in query, the search will only be limited to a specific folder and therfore the query time will be faster.
