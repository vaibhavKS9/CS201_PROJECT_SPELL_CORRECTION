//SPELL CORRECTION USING TERNARY SEARCH TREE

this project uses ternary search tree(TST) for spell correction.
~Firstly it stores all the words from words.txt file attached in the same zip(Code_file_Group_5.zip) file.

~Secondly after storing its uses traversal and searching of ternery search tree to spell correct using the following algorithm:
the pseudocode of algorithm is given as follows:
pseudocode-

//word_arr stores all the dictionary from min length to maximum length words which have similar letters as of the input word
//key is input word for correction

// case0:when the word is already correct that is it is present in the TST dictionary

if(search(input)==1){
	print(input word);
	return;
`	}

// case1:when the error is because of one letter of the input word is misplaced with adjacent letter in keyboard
for(i=0 to i=length of string-1){
	new_key=replace(key[i] with it's adjacent keyboard letter);
 	if search(new_key)==1{ 
		print(new_key);
		return ;
		}

// case2:when one letter at the end of the input word is missing then, we combine all the input words with 26 letters of alphabets(one by one) and check if itis present in TST dictionary
char temp=key;
for(i=97 to 122){
	temp+char(i);       //new string that will have additional letter at the end
	if(search(temp)==1){
		print(temp)
`		return;
		}

//case3:when one word is incorrect in input word because of one additional letter at the end of input word, the we delete the last letter and search in TST
char temp=key[0,1,...length of string-2];
if(search(temp)==1){
	print(temp)
	return
	}

//case4: In last case it returns the "minimum length dictionary word" with maximum similar letter of input word// it traverses the input word uptill that input word can make up any english word,
 	after that it stores all possible word with those similar letter that can make an english word in word_arr and returns simply the min length alphabetiically ordererd word.  
	i.e return word_arr[0];

//search func used is the ternary search tree search function
//word_arr stores the words using modifying the search trees and finally stores all the words having maximum similar letters from input word.

-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-

~The following function are the main functions used for algorithm


~int replace(struct Node *root,char* word,char c,int uptill)
	//This function just simply replaces every letter with adjacent character in keyboard and then checks from search function if the the replaced word is in TST if yes then returns that word immediately

~int search_similar(struct Node *root, char *word,char*key)
	// This function to search for the dictionary word with similar letters of input word that could make up dictionary word and then uses traverse function to find all the possible dictionary word with those similar letter in input word.


//WHILE RUNNING THE PROGRAM KINDLY INPUT THE WORD FOR CORRECTION IN ***SMALL CASES ONLY****
//FOLLOWING ARE SOME THE TEST CASES RUNNED WITH THEIR OUTPUTS

INPUT                     OUTPUT

milk			word milk is already correct				 //CASE 0
consistent		word consistent is already correct

spwech			corrected form of spwech should be speech                 //CASE1
sperch			corrected form of sperch should be speech
pasdion			corrected form of pasdion should be passion
pasuon			corrected form of passuon should be passion
entrepremeur		corrected form of entrepremeur should be entrepreneur

fil			corrected form of fil should be file                      //CASE2
unwra			corrected form of unwra should be unwrap
utilit			corrected form of utilit should be utility
variet			corrected form of variet should be variety
tomorro			corrected form of tomorro should be tomorrow

milkd			correct form of milkd should be milk                      //CASE 3
toolkity		correct form of toolkity should be toolkit
tourismn		correct form of tourismn should be tourism
universityu		correct form of universityu should be university
remediesa		correct form of remediesa should be remedies

entrepgsg		correct form of entrepgsg might be entrepreneur		  //CASE 4
polansdgg		correct form of polansdgg might be poland
rememsfas		correct form of rememsfas might be remember
filtfgs			correct form of filtfgs might be filter
abanfer			correct form of abanfer might be abandoned
			



















































