using namespace std;

#include "classes.h"

/**
    This file contains the functions which are used in the statistics component. Also contained is the function used for
    troublshooting, called "print_info", located at the very bottom of the file.
**/

void count_affiliations(ALL_Cards *all_cards, ALL_Cards *unique_affiliations, Affiliation_Array *aff_counter){

    /**
        Counts cards that share a specific set of affiliations.
        It will count both all cards in its database and the corresponding unique rarity profiles that
        have at least the specified affiliations
    **/

    int i,j,k, unique_counter=0, tracker, rarity_tracker[5], unique_rarity_tracker[5];
    int print_choice;
    string numText;
    vector<int> match_tracker;

    for(i=0;i<5;i++){
        rarity_tracker[i]=0;
        unique_rarity_tracker[i]=0;
    }

    for(i=0;i<all_cards->number_of_characters;i++){
        tracker=0;
        for(j=0;j<all_cards->card[i].number_of_types;j++){
            for(k=0;k<aff_counter->number_of_affiliations;k++){
                if(aff_counter->affiliation[k].aff_name==all_cards->card[i].cardtypes[j]){
                    tracker++;
                }
            }
        }
        if(tracker==aff_counter->number_of_affiliations){
            match_tracker.push_back(i);
            rarity_tracker[(all_cards->card[i].rarity)-1]++;
        }
    }

    for(i=0;i<unique_affiliations->number_of_characters;i++){
        tracker=0;
        for(j=0;j<unique_affiliations->card[i].number_of_types;j++){
            for(k=0;k<aff_counter->number_of_affiliations;k++){
                if(aff_counter->affiliation[k].aff_name==unique_affiliations->card[i].cardtypes[j]){
                    tracker++;
                }
            }
        }
        if(tracker==aff_counter->number_of_affiliations){
            unique_counter++;
            unique_rarity_tracker[(unique_affiliations->card[i].rarity)-1]++;
        }
    }

    if(aff_counter->number_of_affiliations==1){
        cout << "\n\n\tNumber of Profiles with cardtype:  ";
    }else{
        cout << "\n\tNumber of Profiles possessing cardtypes:  ";
    }

    for(i=0;i<aff_counter->number_of_affiliations;i++){
        cout << aff_counter->affiliation[i].aff_name;
        if(i+1<aff_counter->number_of_affiliations){
            cout << " and ";
        }
    }

    cout << "\n";

    cout << "\n\t\tUnique: " << unique_counter << "  (";
    for(i=5;i>0;i--){
        cout << unique_rarity_tracker[i-1] << "  " << i << "*";
        if(i-1>0){
            cout << ",  ";
        }else{
            cout << ")" << "\n";
        }
    }
    cout << "\t\tCharacter: " << match_tracker.size() << "  (";

    for(i=5;i>0;i--){
        cout << rarity_tracker[i-1] << "  " << i << "*";
        if(i-1>0){
            cout << ",  ";
        }else{
            cout << ")" << "\n";
        }
    }

    if(match_tracker.size()>0){
        cout << "\n\nPrint out Character names to txt file? (Yes = 1):  ";
        cin >> numText;
        print_choice=StringToInt(numText);

        if(print_choice!=1){
            cin.clear();
            cin.ignore(256,'\n');
            print_choice=0;
        }

        if(print_choice){
            ofstream myoutput;
            string filename="CharacterProfiles/";

            filename.append(aff_counter->affiliation[0].aff_name);

            for(i=1;i<aff_counter->number_of_affiliations;i++){
                filename.append("_");
                filename.append(aff_counter->affiliation[i].aff_name);
            }

            filename.append(".txt");

            myoutput.open(filename.c_str());

            for(i=0;i<match_tracker.size();i++){
                myoutput << all_cards->card[match_tracker[i]].name << "\n";
                myoutput << "\tRarity:  " << all_cards->card[match_tracker[i]].rarity << "\tCost:  " << all_cards->card[match_tracker[i]].cost;
                if(all_cards->card[match_tracker[i]].is_awakened){
                    myoutput << "\tAwakened";
                }

                if(i+1<match_tracker.size()){
                    myoutput << "\n\n";
                }
            }

            myoutput.close();

            cout << "\n\n\tCharacter names printed to 'CharacterProfiles'\n\n";
        }
}

}


void number_of_profiles(ALL_Cards *all_cards, ALL_Cards *unique_profiles){

    /** Counts all cards and all unique affiliations that are in the database and prints to screen **/

    cout << "\n\n\tThere are " << all_cards->number_of_characters << " total character cards and " << unique_profiles->number_of_characters << " unique affiliation profiles in this database\n";

}


void return_affiliation_numbers(ALL_Cards *all_cards, ALL_Cards *unique_profiles, int number){

    /** Counts and prints to screen all cards and unqiue profiles that have exactly N affiliations **/

    int i, counter=0, unique_counter=0;

    if(number<=all_cards->max_affiliations){
        for(i=0;i<all_cards->number_of_characters;i++){
            if(all_cards->card[i].number_of_types==number){
                counter++;
            }
        }

        for(i=0;i<unique_profiles->number_of_characters;i++){
            if(unique_profiles->card[i].number_of_types==number){
                unique_counter++;
            }
        }
    }

    cout << "\n\n\tThere are " << counter << " character cards and " << unique_counter << " unique profiles possessing " << number << " different types\n";

}


void print_rarity(ALL_Cards *all_cards, ALL_Cards *unique_affiliations){

    /** Counts and prints to screen the number of cards and unique profiles of each rarity **/

    const int maxCharRarity=all_cards->max_rarity, minCharRarity=all_cards->min_rarity;
    const int CharRarityDiff=maxCharRarity-minCharRarity+1;
    int i;
    int *character_rarity = new int[CharRarityDiff];
    int *unique_rarity= new int[CharRarityDiff];

    for(i=0;i<CharRarityDiff;i++){
        character_rarity[i]=0;
        unique_rarity[i]=0;
    }

    for(i=0;i<all_cards->number_of_characters;i++){
        character_rarity[all_cards->card[i].rarity-minCharRarity]+=1;
    }

    for(i=0;i<unique_affiliations->number_of_characters;i++){
        unique_rarity[unique_affiliations->card[i].rarity-minCharRarity]+=1;

    }

    for(i=0;i<CharRarityDiff;i++){
        if(character_rarity[i]!=0){
            cout << "\tThere are " << character_rarity[i] << " " << i+minCharRarity << "* character cards" ;
            cout << "  (" << unique_rarity[i] << " unique profiles)\n";
        }
    }

    cout << "\n";

    delete [] character_rarity;
    delete [] unique_rarity;
}


void track_awaken(ALL_Cards *all_cards, ALL_Cards *unique_affiliations){

    /** Counts and prints to screen the awakened cards in the database **/

    const int maxCharRarity=all_cards->max_rarity, minCharRarity=all_cards->min_rarity;
    const int CharRarityDiff=maxCharRarity-minCharRarity+1;
    int i;
    int *character_awaken= new int[CharRarityDiff];
    int *unique_awaken= new int[CharRarityDiff];

    for(i=0;i<CharRarityDiff;i++){
        character_awaken[i]=0;
        unique_awaken[i]=0;
    }

    for(i=0;i<all_cards->number_of_characters;i++){
        character_awaken[all_cards->card[i].rarity-minCharRarity]+=all_cards->card[i].is_awakened;
    }

    for(i=0;i<unique_affiliations->number_of_characters;i++){
        unique_awaken[unique_affiliations->card[i].rarity-minCharRarity]+=unique_affiliations->card[i].is_awakened;
    }

    cout << "\n\n";

    for(i=0;i<CharRarityDiff;i++){
        if(character_awaken[i]!=0){
            cout << "\tThere are " << character_awaken[i] << " " << i+minCharRarity << "* awakened character cards" ;
            cout << "  (" << unique_awaken[i] << " unique awakened profiles)\n";
        }
    }

    cout << "\n";
    delete [] character_awaken;
    delete [] unique_awaken;
}


void count_affiliation_spread(ALL_Cards *all_cards){

    /**
        This function produces one output text file to the "UniqueProfiles" directory:
            "unique_profile_dist.txt"
                -Counts how many cards possess each unique affiliation profile
    **/

    int i,j, sum_tracker;
    vector< vector<unsigned long int> > sum_array;
    vector<unsigned long int> sum_column_values (3);

    ofstream myoutput;
    sum_column_values[0]=all_cards->card[0].affiliation_sum;
    sum_column_values[1]=1;
    sum_column_values[2]=0;
    sum_array.push_back(sum_column_values);

    for(i=1;i<all_cards->number_of_characters;i++){
        sum_tracker=0;
        for(j=0;j<sum_array.size();j++){
            if(sum_array[j][0]!=all_cards->card[i].affiliation_sum){
                sum_tracker++;
            }else
                if(sum_array[j][0]==all_cards->card[i].affiliation_sum){
                    sum_array[j][1]++;
                }
        }
        if(sum_tracker==sum_array.size()){
            sum_column_values[0]=all_cards->card[i].affiliation_sum;
            sum_column_values[1]=1;
            sum_column_values[2]=i;
            sum_array.push_back(sum_column_values);
        }

    }

    myoutput.open("UniqueProfiles/unique_profile_dist.txt");

    if(myoutput.is_open()){
        for(i=0;i<sum_array.size();i++){
            if(sum_array[i][1]==1){
                myoutput << "There is " << sum_array[i][1] << " character card which is exactly: ";
            }else{
                myoutput << "There are " << sum_array[i][1] << " character cards which are exactly: ";
            }

            for(j=0;j<all_cards->card[sum_array[i][2]].number_of_types;j++){
                myoutput << all_cards->card[sum_array[i][2]].cardtypes[j];
                if(j+1<all_cards->card[sum_array[i][2]].number_of_types){
                    myoutput << ", ";
                }
            }

            if(i+1<sum_array.size()){
                myoutput << "\n\n";
            }
        }

        myoutput.close();
    }

    cout << "\n\n\tAffiliation distributions printed to folder 'UniqueProfiles'\n";
}


void print_skills(AllSupportSkills allsupportskills){

    /**
        An interactive component. Main function is to print out information about support cards - names,
        rarity, requirements, max levels, etc. Two options: print by list or print by user choice
    **/

    int choice, skill_choice, i,j,k, list_on=1;
    string numText;

    cout << "\nPrint all skills (1) or choose from a list (2)?:  ";
    cin >> numText;
    choice=StringToInt(numText);

    while(choice<1 || choice>2){
        cin.clear();
        cin.ignore(256,'\n');
        cout << "Invalid choice. Enter again:  ";
        cin >> numText;
        choice=StringToInt(numText);
    }
    cout << "\n\n";

    if(choice==1){
        for(i=0;i<allsupportskills.numberOfSkills;i++){
            cout << "\t" << allsupportskills.supportskill[i].skillName << ", Max Level: " << allsupportskills.supportskill[i].max_level << "\n";
            cout << "\n\tCards:\n";
            for(j=0;j<allsupportskills.supportskill[i].numberOfCards;j++){
                cout << "\t\t" << allsupportskills.supportskill[i].supportskillcard[j].rarity << "* " << allsupportskills.supportskill[i].supportskillcard[j].charactername << "\n";
                cout << "\t\t\trequires " << allsupportskills.supportskill[i].supportskillcard[j].numTypeReq << " cardtypes (";
                for(k=0;k<allsupportskills.supportskill[i].supportskillcard[j].numTypeReq;k++){
                    cout << allsupportskills.supportskill[i].supportskillcard[j].types_needed[k];

                    if(k+1<allsupportskills.supportskill[i].supportskillcard[j].numTypeReq){
                        cout << " and ";
                    }else{
                        cout << ")\n";
                    }
                }
                cout << "\t\t\tCardType requirements per level: ";
                for(k=0;k<allsupportskills.supportskill[i].max_level;k++){
                    cout << allsupportskills.supportskill[i].supportskillcard[j].supportskillreqs[k].typereq;

                    if(k+1<allsupportskills.supportskill[i].max_level){
                        cout << "   ";
                    }
                }
                cout << "\n\n";
            }
            cout << "\nEnter any number to quit or enter any other value to continue ...\n";
            cin >> list_on;
            if(!(cin.good())){
                cin.clear();
                cin.ignore(256, '\n');
            }else{
                break;
            }
        }
    }else
        if(choice==2){
            do{
                for(i=0;i<allsupportskills.numberOfSkills;i++){
                    cout << i+1 << ")  " << allsupportskills.supportskill[i].skillName << "\n";
                }
                cout << "\nPlease choose a support skill:  ";
                cin >> numText;
                skill_choice=StringToInt(numText);

                while(skill_choice>allsupportskills.numberOfSkills || skill_choice<1){
                    cin.clear();
                    cin.ignore(256, '\n');
                    cout << "\nInvalid choice. Please enter again:  ";
                    cin >> numText;
                    skill_choice=StringToInt(numText);
                }

                i=skill_choice-1;

                cout << "\n\n\t" << allsupportskills.supportskill[i].skillName << ", Max Level: " << allsupportskills.supportskill[i].max_level << "\n";
                cout << "\n\tCards:\n";

                for(j=0;j<allsupportskills.supportskill[i].numberOfCards;j++){
                    cout << "\t\t" << allsupportskills.supportskill[i].supportskillcard[j].rarity << "* " << allsupportskills.supportskill[i].supportskillcard[j].charactername << "\n";
                    cout << "\t\t\trequires " << allsupportskills.supportskill[i].supportskillcard[j].numTypeReq << " cardtypes (";
                    for(k=0;k<allsupportskills.supportskill[i].supportskillcard[j].numTypeReq;k++){
                        cout << allsupportskills.supportskill[i].supportskillcard[j].types_needed[k];

                        if(k+1<allsupportskills.supportskill[i].supportskillcard[j].numTypeReq){
                            cout << " and ";
                        }else{
                            cout << ")\n";
                        }
                    }
                    cout << "\t\t\tCardType requirements per level: ";
                    for(k=0;k<allsupportskills.supportskill[i].max_level;k++){
                        cout << allsupportskills.supportskill[i].supportskillcard[j].supportskillreqs[k].typereq;

                        if(k+1<allsupportskills.supportskill[i].max_level){
                            cout << "   ";
                        }
                    }
                    cout << "\n\n";
                }

                cout << "\nCheck another skill? (Yes = 1):  ";
                cin >> numText;
                list_on=StringToInt(numText);

                if(list_on!=1){
                    list_on=0;
                }

            }while(list_on);
        }

}


void print_exact_profiles(ALL_Cards *all_cards){

    /**
        Prints multiple text output to directory "CharacterProfiles/ExactProfiles"
        The files produced list the cards (name, rarity, cost, and awakened state)
        which possess the stated affiliations (the title of the text file). Output
        is only produced for combinations of affilations which exist in the database.
    **/

    int i,j,k,l, not_in_array=0;
    unsigned long int current_sum;
    vector<unsigned long int> affiliation_sum_tracker;
    string filename, txt=".txt";
    ofstream myoutput;

    for(i=0;i<all_cards->number_of_characters;i++){
        not_in_array=0;

        for(j=0;j<affiliation_sum_tracker.size();j++){
            if(all_cards->card[i].affiliation_sum!=affiliation_sum_tracker[j]){
                not_in_array++;
            }
        }

        if(not_in_array==affiliation_sum_tracker.size()){
            current_sum=all_cards->card[i].affiliation_sum;

            filename="CharacterProfiles/ExactProfiles/";
            filename.append(all_cards->card[i].cardtypes[0]);

            for(k=1;k<all_cards->card[i].number_of_types;k++){
                filename.append("_");
                filename.append(all_cards->card[i].cardtypes[k]);
            }

            filename.append(txt);

            myoutput.open(filename.c_str());

            for(l=i;l<all_cards->number_of_characters;l++){
                if(all_cards->card[l].affiliation_sum==current_sum){
                    myoutput << all_cards->card[l].name << "\n";
                    myoutput << "Rarity: " << all_cards->card[l].rarity << "*\t\tCost: " << all_cards->card[l].cost << "\n\n";
                }
            }

            myoutput.close();

            affiliation_sum_tracker.push_back(current_sum);
        }
    }

    cout << "\n\n\tExact Profiles Updated.\n\n";
}


void check_stats(ALL_Cards *all_cards, ALL_Cards *unique_cards, Affiliation_Array *affiliation_array, AllSupportSkills *allsupportskills){

    /**
        This is the function which combines all the statistics components. This is called from main and it lets the
        user select which statistic they wish to run (or sometimes print) to text file output. It will run one selection
        and then ask if the user wishes to continue checking stats or if they're ready to proceed.
    **/

    int choice, finished=0, affiliation_number=0, translator, i, new_search;
    string numText;

    do{
        cout << "\n(1) Number of cards\n";
        cout << "(2) Number of cards of rarity X\n";
        cout << "(3) Number of Awakened Cards\n";
        cout << "(4) Number of cards who have exactly N affiliations\n";
        cout << "(5) Number of cards possessing exactly N specified affiliations\n";
        cout << "(6) Distribution of Affiliations\n";
        cout << "(7) List Support Abilities\n";
        cout << "(8) Update Exact Profiles\n";
        cout << "\nSelect which stat (1-8) you wish to check:  ";

        cin >> numText;
        choice=StringToInt(numText);

        while(choice>8 || choice<1){
            cout << "Invalid choice. Please enter again: ";
            cin >> numText;
            choice=StringToInt(numText);
        }

        if(choice==1){
            number_of_profiles(all_cards, unique_cards);
        }else
            if(choice==2){
                print_rarity(all_cards, unique_cards);
            }else
                if(choice==3){
                    track_awaken(all_cards, unique_cards);
                }else
                    if(choice==4){
                        cout << "\nExactly how many affiliations?: ";
                        cin >> numText;
                        affiliation_number=StringToInt(numText);

                        while(affiliation_number<0){
                            cout << "Invalid choice. Please enter again: ";
                            cin >> numText;
                            affiliation_number=StringToInt(numText);
                        }

                        return_affiliation_numbers(all_cards, unique_cards, affiliation_number);
                    }else
                        if(choice==5){
                            cout << "\n";
                            for(i=0;i<affiliation_array->number_of_affiliations;i++){
                                cout << right << setfill(' ') << setw(2) << i+1 << ")" << left << setw(23) << affiliation_array->affiliation[i].aff_name << "  ";

                                if(i%5==4){
                                    cout << "\n";
                                }
                            }

                            while(aff_counter.affiliation.size()>0){
                                aff_counter.affiliation.pop_back();
                            }

                            cout << "\n\n\nSelect which affiliation(s) (1-" << affiliation_array->number_of_affiliations << ") you wish to search, then press enter\nEnter 0 to start search:\n";

                            do{
                                cin>>numText;
                                translator=StringToInt(numText);

                                if(translator<0 || translator>affiliation_array->number_of_affiliations){
                                    cout << "\n\tInvalid entry\n";
                                }else
                                    if(translator==0){
                                        break;
                                    }else{
                                        new_search=0;

                                        for(i=0;i<aff_counter.affiliation.size();i++){
                                            if(aff_counter.affiliation[i].type_value!=affiliation_array->affiliation[translator-1].type_value){
                                                new_search++;
                                            }
                                        }

                                        if(new_search==aff_counter.affiliation.size()){
                                            aff_counter.affiliation.push_back(Affiliation());
                                            aff_counter.affiliation[new_search].aff_name=affiliation_array->affiliation[translator-1].aff_name;
                                            aff_counter.affiliation[new_search].type_value=affiliation_array->affiliation[translator-1].type_value;
                                        }
                                    }

                                if(aff_counter.affiliation.size()==affiliation_array->number_of_affiliations){
                                    break;
                                }

                            }while(1==1);

                            aff_counter.number_of_affiliations=aff_counter.affiliation.size();

                            cout << "\n";

                            count_affiliations(all_cards,unique_cards,&aff_counter);
                        }else
                            if(choice==6){
                                count_affiliation_spread(all_cards);
                            }else
                                if(choice==7){
                                    print_skills(*allsupportskills);
                                }else
                                    if(choice==8){
                                        print_exact_profiles(all_cards);
                                    }

        cout << "\n\nCheck more stats? (Yes = 1): ";
        cin >> finished;

        if(!(cin.good())){
            cin.clear();
            cin.ignore(256,'\n');
            finished=0;
        }

    }while(finished);

}


void print_info(AllSupportSkills *allsupportskills, ALL_Cards *all_cards){

    /**
        This component is the one mainly used for error checking. It is called directly from main, and it prints to screen
        information about the cards in the database: name, rarity, cost, awakened state, support skill, level requirements,
        affiliations, and their position in the database.

        When called, the user has the option to either list all the cards (sequential from position 0 to Max Character) or
        have them listed randomly.
    **/

    int x, i, counter, choice, rand_char, start, list_on=1;
    string numText;

    cout << "List (1) or random (2) or Quit (0)?: ";
    cin >> numText;
    start=StringToInt(numText);
    if(start>2 || start <1){
        start=0;
    }

    if(start==1){
        cout << endl;

        for(counter=0;counter<all_cards->number_of_characters;counter++){
            cout << all_cards->card[counter].rarity << "* " << all_cards->card[counter].name << " is afilliated with " << all_cards->card[counter].cardtypes[0];
            if(all_cards->card[counter].number_of_types>1){
                for(x=1;x<all_cards->card[counter].number_of_types;x++){
                    cout << " and " << all_cards->card[counter].cardtypes[x];
                }
            }
            cout << ".\n";

            if(all_cards->card[counter].is_awakened){
                cout << "This card can be awakened.\n";
            }else{
                cout << "This card cannot be awakened.\n";
            }

            if(all_cards->card[counter].has_skill){
                cout << all_cards->card[counter].rarity << "* " << all_cards->card[counter].name << " has skill " << all_cards->card[counter].skillname << ", which requires:\n";
                for(x=0;x<allsupportskills->supportskill[all_cards->card[counter].skill_ID].max_level;x++){
                    cout << "\t" << allsupportskills->supportskill[all_cards->card[counter].skill_ID].supportskillcard[all_cards->card[counter].skillcard_ID].supportskillreqs[x].typereq << " of ";
                    for(i=0;i<allsupportskills->supportskill[all_cards->card[counter].skill_ID].supportskillcard[all_cards->card[counter].skillcard_ID].numTypeReq;i++){
                        cout << "(" << allsupportskills->supportskill[all_cards->card[counter].skill_ID].supportskillcard[all_cards->card[counter].skillcard_ID].types_needed[i] << ")  ";
                    }
                    cout << " for level " <<  allsupportskills->supportskill[all_cards->card[counter].skill_ID].supportskillcard[all_cards->card[counter].skillcard_ID].supportskillreqs[x].level << endl;
                }
            }else{
                cout << all_cards->card[counter].rarity << "* " << all_cards->card[counter].name << " does not have a skill.\n";
            }
            cout << all_cards->card[counter].rarity << "* " << all_cards->card[counter].name << " costs " << all_cards->card[counter].cost << " points.\n";

            cout << "Database ID: " << counter << endl << endl;

            if(counter%15==14){
                cout << "\nInput any number to quit or any other value to continue ...\n";
                cin >> list_on;
                if(!(cin.good())){
                    cin.clear();
                    cin.ignore(256, '\n');
                }else{
                    break;
                }
            }
        }

    }else
        if(start==2){

            srand(time(NULL));

            do{
                rand_char=rand()%all_cards->number_of_characters;
                cout << "\n\n" << all_cards->card[rand_char].rarity << "* " << all_cards->card[rand_char].name << " is afilliated with " << all_cards->card[rand_char].cardtypes[0];
                    if(all_cards->card[rand_char].number_of_types>1){
                        for(x=1;x<all_cards->card[rand_char].number_of_types;x++){
                            cout << " and " << all_cards->card[rand_char].cardtypes[x];
                        }
                    }
                    cout << ".\n";

                    if(all_cards->card[rand_char].is_awakened){
                        cout << "This card can be awakened.\n";
                    }else{
                        cout << "This card cannot be awakened.\n";
                    }

                    if(all_cards->card[rand_char].has_skill){
                        cout << all_cards->card[rand_char].rarity << "* " << all_cards->card[rand_char].name << " has skill " << all_cards->card[rand_char].skillname << ", which requires:\n";
                        for(x=0;x<allsupportskills->supportskill[all_cards->card[rand_char].skill_ID].max_level;x++){
                            cout << "\t" << allsupportskills->supportskill[all_cards->card[rand_char].skill_ID].supportskillcard[all_cards->card[rand_char].skillcard_ID].supportskillreqs[x].typereq << " of ";
                            for(i=0;i<allsupportskills->supportskill[all_cards->card[rand_char].skill_ID].supportskillcard[all_cards->card[rand_char].skillcard_ID].numTypeReq;i++){
                                cout << "(" << allsupportskills->supportskill[all_cards->card[rand_char].skill_ID].supportskillcard[all_cards->card[rand_char].skillcard_ID].types_needed[i] << ")  ";
                            }
                            cout << " for level " <<  allsupportskills->supportskill[all_cards->card[rand_char].skill_ID].supportskillcard[all_cards->card[rand_char].skillcard_ID].supportskillreqs[x].level << endl;
                        }
                    }else{
                        cout << all_cards->card[rand_char].rarity << "* " << all_cards->card[rand_char].name << " does not have a skill.\n";
                    }
                    cout << all_cards->card[rand_char].rarity << "* " << all_cards->card[rand_char].name << " costs " << all_cards->card[rand_char].cost << " points.\n";

                cout << "Database ID: " << rand_char << endl;
                cout << "\n\nRun again? (Yes = 1):  ";
                cin >> numText;
                choice=StringToInt(numText);
                if(choice!=1){
                    choice=0;
                }
                cout << "\n\n";

            }while(choice);
        }

    }
