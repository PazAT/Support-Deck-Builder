# Support-Deck-Builder
A brute force solver for Support Decks in SWFC

+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Readme for the Support Deck Builder

	I. Introduction & Description
	II. Installation
	III. Files Used
	IV. Understanding the Files
	V. Output
		V.i Support Output
		V.ii Unique Profile Output
		V.iii Character Profile Output
	VI. Editing Files

++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	
	I. Introduction & Description
	
This program's primary purpose is to brute force solve for 2-6 skill support deck combinations given sets of character affiliations. It solves by
assuming each avaliable card is at the highest possible build - emax or awakened. If combinations are located, they are printed to a ".txt" document
located in the "Output" directory. If no combinations are located, the output file(s) is notated as such and a printout appears on screen notifying the
user that no combinations could be located. In addition, this program contains a statistics feature for analyzing various information about the
characters and unique profiles.

Included are five controllable optimizations for searching:
		
	1) thresholding cards to search based on N affiliation matches
		-With this option, the user specifies N affiliations a card must match of the total needed affiliations for a support deck
		-e.g., if Queen Apaliana and Dexster Jettster were your cards, and you entered "2" as your type match criteria, the program would only search cards who match
		-at least 2 of their needed affiliations: So it would only search cards who match at least two of {Male, Naboo, Galactic Empire, and Galactic Republic}
	
	2) limiting searches to N* affiliation sets or better
		-This option allows the user to control through how many levels of rarity are searched. The program starts searching at 5* and
		-progresses through lesser rarities. Note that including more lower rarities can increase the solve time drastically.
	
	3) Stop searching after the first N solutions have been found
		-User sets a number N of solutions they want found and the program will stop searching after N solutions have been found
		
	4) Ignoring skill cards during search
		-User can select certain skill cards to exclude during solving
	
	5) thresholding solutions based on total cost
		-The user sets a maximum cap cost for their support deck, and the solver excludes all solutions whose minimum cap cost is
		-greater than the user defined value.


Once these options have been set, the program will commence its solving. Solving can take at few as 3 seconds, or as long as 10 minutes, depending
on the skills and options chosen. This is a brute force solver, so the program will search through every viable combination specified by the chosen
options until all possible combinations have been examined.

++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	II. Installation
	
Please see the file "Getting Started.txt" for installation instructions.
	
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	III. Files Used

All files accessed by this program are in a local directory called "Data". The program uses these files to build its database of support skills, cards,
and affiliations. Editing these files changes what data the program sees, and so it is advised that you do not edit them without reading the
how-to-edit the files in section VI.
The reason this information exists in .txt form and not in the source code is that it is designed to be more fluid with the release of new support
abilities and cards. Instead of needing to edit the source code with each release one simply edits the correpsonding .txt file(s). This also allows
the user an easy way to exclude items they do not want considered.

Inside of "Data", there are six .txt files and one .xlsx excel file. These files are:

	1) cardTypes.txt
	2) characterNames.txt
	3) numericTypes.txt
	4) supportCards.txt
	5) supportSkillLevels.txt
	6) supportSkills.txt
	7) Support Deck Tables.xlsx

Each line in numericTypes.txt has a matching character in the characterNames.txt file (1:1 map). However, each line in
supportSkillLevels.txt does not have a matching line in supportCards.txt (not 1:1 map). More information is available in
the next section.
			
The only file not referenced by the program is "Support Deck Tables.xlsx". That file is just a simple spreadsheet to make editing information about cards and skills easier.

++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	IV. Understanding the Files
	
The "Data" files are the program's database, so to speak. In particular, the files "numericTypes.txt" and "supportSkillLevels.txt" are the most
important and coincidentally, the most cryptic upon first glance. Each of these files contains numerical information pertaining to characters and
support skills, respectively. In contrast, the other files are simpler to read.

	supportSkills.txt
		the name of each support skill and its nickname on the line directly below
			<support skill full name>
			<support skill nickname>
			
		For example, HP UP is represented as:
			Character Card HP UP
			HP
	
	supportCards.txt
		The name of each support card and the types it requires for its skill. The order of names here must correspond to the order of support
		skills in "supportSkills.txt", otherwise cards will be assigned to the incorrect skill. Each entry uses commas to separate items on the
		same line - the very last item on a line should have no comma after it. For cards with fewer than three requirements, they are marked
		with "None" for the excess requirements.
		
		Some examples:
			First Ambush entry:
				Agen Kolar,Jedi,Clone Trooper,None
				
			Battle Penalty Reduction entries:
				Jabba the Hutt,Jabbas Crime Syndicate,None,None
				Sebulba,Podracer,None,None
				
			Jamillia from Prep Skill Trigger UP
				Queen Jamillia,Female,Jedi,Nabooan
		
	*** supportSkillLevels.txt ***
		This file contains numerical information about the skills and skill cards. The order of information must correspond first to the order of
		support skills in "supportSkills.txt" and then second to the ordering of support cards in "supportCards.txt" or else information about a
		skill and its cards will be wrong.
		
		The start of each new skill is marked by a line that contains only two integers, which represent the following:
		
					<skill max level>	<number of cards with this support skill>

		Following this line is a variable number of lines with a variable number of integers on each line. The number of lines which follow is
		equal to the second number on the first line - each of those lines represent an individual skill card. On each of those lines, the number
		of integers is equal to the [skill max level] + 1. The first N integers represent the type value requirements for each level of a skill
		with max level N and the very last integer on the line is the skill card's rarity.
		
		The template for a skill card line is as follows
		
					<skill level 1 type requirement> ... <skill level MAX type requirement>	<skill card rarity>

		So Character Card HP UP would look like the following:
		
			5 4
			3 5 7 9 12 2
			3 5 7 9 12 2
			3 5 7 9 12 3
			3 5 7 9 12 2

		The first line tells us that Character Card HP UP has "5" max levels and "4" Character Cards possess it. The next 4 lines then tell us
		the individual value requirements for each skill card that has HP UP and the rarity of that skill card. So we see that the first card has
		value requirements of "3", "5", "7", "9", and "12" for levels 1 to 5, and it is rarity "2". The first card of this skill corresponds
		to Rabe in the file "supportCards.txt"
		
		Looking at Call to the Light Side,
		
			1 3
			4 4
			4 4
			4 3
			
		We can see that the skill has "1" max level and "3" Character Cards possess it. The first of these cards requires "4" type values and it is
		of rarity "4". The first card of this skill correpsonds to Adi Gallia in the file "supportCards.txt".
		
		Note that not every two integer line is a start of a new skill card - with skills that have only 1 max level, their entries are all two
		integer lines. For more insight on this file, please look at the "SS output" page in the excel spreadsheet "Support Deck Tables.xlsx".
		


	----------------------------------------------------------------------------------------------------------------------
	
	
			
	cardTypes.txt
		This file contains the name of each affiliation in the current game. Only one affiliation per line.

	characterNames.txt
		In here are the full names of the Character Cards. One character per line.

	*** numericalTypes.txt ***
		Inside here, you'll find many lines, each of 5 sets of numbers. These numbers are tab spaced and each relates to a line in the file
		"characterNames.txt". The entry method for "numericalTypes.txt" is as follows:

						<rarity>	<cap cost>	<number of affilaitions>	<affiliation sum>	<awakened status (binary representation)>

		So, the first value of a line is a card's rarity, the second is its cost, and the third is how many affiliations that card possesses. The
		fourth value is generated by assigning a unique integer to each affiliation and then summing the unique integers of the affiliations
		belonging to a card. The last value represents if a card is awakened ("1" if it is and "0" if it is not).
		
		The affiliation sum is generated by using powers of 2. The power given to an affiliation is equal to how many affiliations are before it
		in the file "cardTypes.txt". So for "Male", the first listed affiliation, it would have a power equal to "0" (zero) because no affiliation comes
		before it. "Female" would have a power of "1" (since only one affiliation comes before it); "Droid" would have "2"; and so on, down to
		"Fringer", which has a power of "23" because there are 23 affiliations before it.
		
		Taking a look at the very first entry, we see
		
			5	32	3	32786	0
			
		And since "numericTypes.txt" has a line for every line in "characterNames.txt", looking at the first line in the latter file tells us that
		we are examining the information for "Aayla Secura".
		
		We see that she is rarity "5", has a cap cost of "32", and has "3" different affiliations. These affiliations sum to "32786" and at the
		current moment, Aayla is not awakened (last value is "0"). Looking at Aayla's affiliations (Female, Jedi, Galactic Republic), we can see
		that the affiliation sum was generated by: 2^1 + 2^4 + 2^15 = 32786. When the program reads this value, it will deconstruct it by using
		the number of affiliation values to pull out Aayla's affiliations in written form.
		
		Choosing another entry (from line 199):
		
			4	15	4	1114241	1
			
		Looking at line 199 in "characterNames.txt", we see that these values belong to "Jango Fett".
		
		This Jango is rarity "4", costs "15", has "4" different types, has an affiliation sum of "1114241", and is awakened (last value is "1").
		Looking at Jango's types in-game, we see that they are: Male, Bounty Hunter, Separatist, and Mandalorian; and so the affiliation sum is
		generated from: 2^0 + 2^7 + 2^16 + 2^20 = 1114241.
			
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	V. Output
	
This program will produce output files to four locations: 1) directory "Output"; 2) directory "UniqueProfiles"; 3) directory "CharacterProfiles"; and 4) "ExactProfiles", a subdirectory of "CharacterProfiles".

"Output" contains the solutions found by the program during its combination searches
"UniqueProfiles" contains information about affiliation distributions of the current set of character cards
"CharacterProfiles" contains the names of Character Cards that possess at least a user specified given set of affiliations
"CharacterProfiles\ExactProfiles" contains the names, rarity, and cost of Character Cards which possess the exact specified
set of affiliations

	V.i Support Output
		
		Files in the Output directory are named based on the nicknames of the skills being searched (e.g., searching for Prep Skill Trigger UP,
		Proximity Alarm, and Character Card HP UP will result in a file by the name of "Prep_Prox_HP.txt"). However, note that each ordering of a
		set of skills, such as (Prep, Prox, HP) and (HP, Prox, Prep), will produce a distinct output file even if the contents of the files would
		be identical.
		
		Also generated is a file with the suffix "_bases" - when searching for specific skill levels, the program will check if each
		successful combination can be made by using just bases of those cards. If you are searching for a minimum skill level, the program will
		name files with the minimum level included - so if you were searching for Null, HP 5, and Prep 5, your output would be written to the
		files called "Null_Hp_5_Prep_5.txt" and "Null_Hp_5_Prep_5_BASE.txt". This directory can easily get overcrowded with various files, so
		it may help to create additional directories inside of the Output directory to hold the solutions discovered.

		An output entry will look like:
			----------------------------------------------------------------------
				Ambush, level 1
				Battle Penalty Reduction, level 4
				Battle Reward Credit UP, level 1
			
			4*  Shadow Stormtrooper   5*  Jabba the Hutt   3*  Greedo
			
			6 (Droid,  Galactic Empire)  17 (Jabbas Crime Syndicate)  4 (Bounty Hunter,  Rebel Alliance)
			
				5*  Male,  Bounty Hunter,  Jabbas Crime Syndicate,  Mandalorian	(calculated with awakened bonus)	(3 character cards with 1 awakened)
				5*  Male,  Bounty Hunter,  Jabbas Crime Syndicate,  Mandalorian	(calculated with awakened bonus)	(3 character cards with 1 awakened)
				5*  Droid,  Rebel Alliance	(2 character cards)
				4*  Droid,  Galactic Empire	(1 character cards)
			
			
			23.8 (Male)  8.6 (Galactic Empire)  8.7 (Tatooinian)  19.5 (Jabbas Crime Syndicate)  14.1 (Bounty Hunter)  10.8 (Mandalorian)  9.6 (Droid)  5.3 (Rebel Alliance)
			
			Minimum cost: 128			Maximum Cost: 171
			
			----------------------------------------------------------------------
						
		At the top of the entry is a block with the skill names and their discovered levels
		Next are the skill cards used (rarity and name)
		In the middle are the type and value requirements for the skill levels listed at the top
		The lower block contains the rarity and affiliations of the cards used in the solution, as well as the number of how many character cards of at least those affiliations exist
		The second line above the bottom is the total affiliation value sums using the above cards
		And lastly is the cost range for the solution


	V.ii Unique Profile Output
	
		Output written to the "UniqueProfile" directory are .txt files which contain information about the current unique affiliation profiles in
		the game. There are two possible files that can be written into that folder from the statistics component:
		
		"Unique_Card_Affiliations.txt" - list of each unique affiliation profile per rarity
		"unique_profile_dist.txt" - number of character cards that possess each unique profile (e.g., how many exactly Jedi & Male & Republic cards)
		
	V.iii Character Profile Output
	
		These .txt files contain the names of Character Cards which have at least a certain combination of affiliations. These output files are
		created from the statistics component and are named based on the affiliations queried - so if you were searching for cards possessing
		"Podracer" and "Tatooinian" and "Resistance", the output file would be named "Podracer_Tatooinian_Resistance.txt".
		
		In the subdirectory "ExactProfiles", the same naming scheme is present, but the only members in each file are
		cards who possess exactly the specified affiliations.

++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	VI. Editing Files

As new cards and support skills are released, it becomes necessary to update the databases used by the program. To help with the editing, an excel spreadsheet
(Support Deck Tables.xlsx) with all the pertinent information has been provided. When adding new cards, make a new entry at the bottom of the "Character Table"
page and add all the necessary information in the same row. Do not enter anything into the columns labeled "NumTypes" or "AffiliationSum" - the spreadsheet
will automatically update those columns when you enter the cards's affiliation data. Then once you've finished updating, use Excel's sort function to sort
the character table so that the entries are sorted by rarity (Column 2: high to low) then by character name (Column 1: A to Z). Finally, copy the sorted names
into the "characterNames.txt" file and copy the next 5 columns (Rarity, Cost, NumTypes, AffiliationSum, IsAwakened) into the "numericTypes.txt" file.
Make sure not to copy the headers into either file.

If a new type is added, make a new entry into the page titled "Affiliation Table" - add the affiliation (type) at the bottom, enter its corresponding
power into the next column, and then make sure that the third column is updated appropiately - it should be
	2^[middle column value].

If a new support skill is introduced, first you should add the name and desired nickname of that support skill into the "supportSkills.txt" file. For simple
convience, it is recommended to add new support skills at the bottom of the file - this makes editing the files "supportSkillLevels.txt"
and "supportCards.txt" significantly easier. If you decide to insert a new support skill somewhere above the last support skill in "supportSkills.txt",
you need to be certain that you have correctly moved the entries of the other skills in the other two text files when you insert the information
about the new support skill. For editing support cards, in the same spreadsheet is a page called "Support Skills". On here, enter all the information
for a new support skill (name, nickname, cards, requirements, rarity, etc.) making sure to follow the templates of the other skills. The data you will
want to copy is located on the following page (page name: "SS Output"). You'll see columns of information with headers - those headers represent the file
into which the corresponding columns should be copied. As you update the information on page "Support Skills", "SS Output" is updated as well. Next to
"SS Output" is a page called "SS Translator" - don't mess with that page; it is an intermediate step for the information on "SS Output".

++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
