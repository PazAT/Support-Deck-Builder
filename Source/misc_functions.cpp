using namespace std;

#include "declarations.h"
#include "classes.h"

void count_affiliations(ALL_Cards *all_cards, ALL_Cards *unique_affiliations, Affiliation_Array *aff_counter){

    int i,j,k, card_counter=0, unique_counter=0, tracker, rarity_tracker[5], unique_rarity_tracker[5];
    int print_choice, match_tracker[MAXCHARACTERS];

    for(i=0;i<5;i++){
        rarity_tracker[i]=0;
        unique_rarity_tracker[i]=0;
    }

    for(i=0;i<all_cards->number_of_characters;i++){
        tracker=0;
        for(j=0;j<all_cards->card[i].number_of_types;j++){
            for(k=0;k<aff_counter->number_of_affiliations;k++){
                if(strcmp(aff_counter->affiliation[k].aff_name,all_cards->card[i].cardtype[j].affiliation)==0){
                    tracker++;
                }
            }
        }
        if(tracker==aff_counter->number_of_affiliations){
            match_tracker[card_counter]=i;
            card_counter++;
            if(all_cards->card[i].rarity==1){
                rarity_tracker[0]++;
            }else
                if(all_cards->card[i].rarity==2){
                    rarity_tracker[1]++;
                }else
                    if(all_cards->card[i].rarity==3){
                       rarity_tracker[2]++;
                    }else
                        if(all_cards->card[i].rarity==4){
                            rarity_tracker[3]++;
                        }else
                            if(all_cards->card[i].rarity==5){
                                rarity_tracker[4]++;
                            }
        }
    }

    for(i=0;i<unique_affiliations->number_of_characters;i++){
        tracker=0;
        for(j=0;j<unique_affiliations->card[i].number_of_types;j++){
            for(k=0;k<aff_counter->number_of_affiliations;k++){
                if(strcmp(aff_counter->affiliation[k].aff_name,unique_affiliations->card[i].cardtype[j].affiliation)==0){
                    tracker++;
                }
            }
        }
        if(tracker==aff_counter->number_of_affiliations){
            unique_counter++;
            if(unique_affiliations->card[i].rarity==1){
                unique_rarity_tracker[0]++;
            }else
                if(unique_affiliations->card[i].rarity==2){
                    unique_rarity_tracker[1]++;
                }else
                    if(unique_affiliations->card[i].rarity==3){
                       unique_rarity_tracker[2]++;
                    }else
                        if(unique_affiliations->card[i].rarity==4){
                            unique_rarity_tracker[3]++;
                        }else
                            if(unique_affiliations->card[i].rarity==5){
                                unique_rarity_tracker[4]++;
                            }
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
    cout << "\t\tCharacter: " << card_counter << "  (";

    for(i=5;i>0;i--){
        cout << rarity_tracker[i-1] << "  " << i << "*";
        if(i-1>0){
            cout << ",  ";
        }else{
            cout << ")" << "\n";
        }
    }

    cout << "\n\nPrint out Character names to txt file? (Yes = 1):  ";
    cin >> print_choice;

    if(!(cin.good()) || print_choice!=1){
        cin.clear();
        cin.ignore(256,'\n');
        print_choice=0;
    }

    if(print_choice==1){
        ofstream myoutput;
        string filename="Character Profiles/";

        filename.append(aff_counter->affiliation[0].aff_name);

        for(i=1;i<aff_counter->number_of_affiliations;i++){
            filename.append("_");
            filename.append(aff_counter->affiliation[i].aff_name);
        }

        filename.append(".txt");

        myoutput.open(filename.c_str());

        for(i=0;i<card_counter;i++){
            myoutput << all_cards->card[match_tracker[i]].name << "\n";
            myoutput << "\tRarity:  " << all_cards->card[match_tracker[i]].rarity << "\tCost:  " << all_cards->card[match_tracker[i]].cost;
            if(all_cards->card[match_tracker[i]].is_awakened==true){
                myoutput << "\tAwakened";
            }

            if(i+1<card_counter){
                myoutput << "\n\n";
            }
        }

        myoutput.close();

        cout << "\n\n\tCharacter names printed to 'Character Profiles'\n\n";
    }

}


void number_of_profiles(ALL_Cards *all_cards, ALL_Cards *unique_profiles){

    cout << "\n\n\tThere are " << all_cards->number_of_characters << " total character cards and " << unique_profiles->number_of_characters << " unique affiliation profiles in this database\n";

}


void return_affiliation_numbers(ALL_Cards *all_cards, ALL_Cards *unique_profiles, int number){

    int i, counter=0, unique_counter=0;

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

    cout << "\n\n\tThere are " << counter << " character cards and " << unique_counter << " unique profiles possessing " << number << " different types\n";

}


void print_rarity(ALL_Cards *all_cards, ALL_Cards *unique_affiliations){

    int i, character_rarity[5], unique_rarity[5];

    for(i=0;i<5;i++){
        character_rarity[i]=0;
        unique_rarity[i]=0;
    }

    for(i=0;i<all_cards->number_of_characters;i++){
        character_rarity[all_cards->card[i].rarity-1]++;
    }

    for(i=0;i<unique_affiliations->number_of_characters;i++){
        unique_rarity[unique_affiliations->card[i].rarity-1]++;
    }

    cout << "\n\n";

    for(i=0;i<5;i++){
        cout << "\tThere are " << character_rarity[i] << " " << i+1 << "* character cards" ;
        cout << "  (" << unique_rarity[i] << " unique profiles)\n";
    }

    cout << "\n";
}


void track_awaken(ALL_Cards *all_cards, ALL_Cards *unique_affiliations){

    int i, character_awaken[5], unique_awaken[5];

    for(i=0;i<5;i++){
        character_awaken[i]=0;
        unique_awaken[i]=0;
    }

    for(i=0;i<all_cards->number_of_characters;i++){
        character_awaken[all_cards->card[i].rarity-1]+=all_cards->card[i].is_awakened;
    }

    for(i=0;i<unique_affiliations->number_of_characters;i++){
        unique_awaken[unique_affiliations->card[i].rarity-1]+=unique_affiliations->card[i].is_awakened;
    }

    cout << "\n\n";

    for(i=0;i<5;i++){
        cout << "\tThere are " << character_awaken[i] << " " << i+1 << "* awakened character cards" ;
        cout << "  (" << unique_awaken[i] << " unique awakened profiles)\n";
    }

    cout << "\n";

}


void count_affiliation_spread(ALL_Cards *all_cards, ALL_Cards *unique_affiliations){

    int i,j,x,y, sum_tracker, sum_array[MAXCHARACTERS][3], sum_array_size=0;

    ofstream myoutput, card_profiles;

    sum_array[0][0]=all_cards->card[0].affiliation_sum;
    sum_array[0][1]=1;
    sum_array[0][2]=0;
    sum_array_size++;

    for(i=1;i<all_cards->number_of_characters;i++){
        sum_tracker=0;
        for(j=0;j<sum_array_size;j++){
            if(sum_array[j][0]!=all_cards->card[i].affiliation_sum){
                sum_tracker++;
            }else
                if(sum_array[j][0]==all_cards->card[i].affiliation_sum){
                    sum_array[j][1]++;
                }
        }
        if(sum_tracker==sum_array_size){
            sum_array[j][0]=all_cards->card[i].affiliation_sum;
            sum_array[j][1]=1;
            sum_array[j][2]=i;
            sum_array_size++;
        }

    }

    myoutput.open("Unique Profiles/unique_profile_dist.txt");

    if(myoutput.is_open()==true){
        for(i=0;i<sum_array_size;i++){
            if(sum_array[i][1]==1){
                myoutput << "There is " << sum_array[i][1] << " character card whom is exactly: ";
            }else{
                myoutput << "There are " << sum_array[i][1] << " character cards who are exactly: ";
            }

            for(j=0;j<all_cards->card[sum_array[i][2]].number_of_types;j++){
                myoutput << all_cards->card[sum_array[i][2]].cardtype[j].affiliation;
                if(j+1<all_cards->card[sum_array[i][2]].number_of_types){
                    myoutput << ", ";
                }
            }

            if(i+1<sum_array_size){
                myoutput << "\n\n";
            }
        }

        myoutput.close();
    }

    card_profiles.open("Unique Profiles/Unique_Card_Affiliations.txt");

    for(x=0;x<unique_affiliations->number_of_characters;x++){
        card_profiles << unique_affiliations->card[x].rarity << "*  ";
        for(y=0;y<unique_affiliations->card[x].number_of_types;y++){
            card_profiles << unique_affiliations->card[x].cardtype[y].affiliation;
            if(y+1<unique_affiliations->card[x].number_of_types){
                card_profiles << ",  ";
            }
        }
        if(x+1<unique_affiliations->number_of_characters){
            card_profiles << "\n";
        }
    }

    card_profiles.close();

    card_profiles.open("Unique Profiles/All_Cards__All_Types.txt");

    for(x=0;x<all_cards->number_of_characters;x++){
        for(y=0;y<all_cards->card[x].number_of_types;y++){
            card_profiles << all_cards->card[x].cardtype[y].affiliation;

            if(y+1<all_cards->card[x].number_of_types){
                card_profiles << "\t";
            }
        }

        if(x+1<all_cards->number_of_characters){
            card_profiles << "\n";
        }
    }

    card_profiles.close();

        cout << "\n\n\tAffiliation distributions printed to folder 'Unique Profiles'\n";


}


void print_skills(AllSupportSkills allsupportskills){

    int choice, skill_choice, i,j,k, list_on=1;

    cout << "\nPrint all skills (1) or choose from a list (2)?:  ";
    cin >> choice;

    while(!(cin.good()) || choice<1 || choice>2){
        cin.clear();
        cin.ignore(256,'\n');
        cout << "Invalid choice. Enter again:  ";
        cin >> choice;
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
                    cout << allsupportskills.supportskill[i].supportskillcard[j].types_needed[k].affiliation;

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
                cin >> skill_choice;

                while(!(cin.good()) || skill_choice>allsupportskills.numberOfSkills || skill_choice<1){
                    cin.clear();
                    cin.ignore(256, '\n');
                    cout << "\nInvalid choice. Please enter again:  ";
                    cin >> skill_choice;
                }

                i=skill_choice-1;

                cout << "\n\n\t" << allsupportskills.supportskill[i].skillName << ", Max Level: " << allsupportskills.supportskill[i].max_level << "\n";
                cout << "\n\tCards:\n";

                for(j=0;j<allsupportskills.supportskill[i].numberOfCards;j++){
                    cout << "\t\t" << allsupportskills.supportskill[i].supportskillcard[j].rarity << "* " << allsupportskills.supportskill[i].supportskillcard[j].charactername << "\n";
                    cout << "\t\t\trequires " << allsupportskills.supportskill[i].supportskillcard[j].numTypeReq << " cardtypes (";
                    for(k=0;k<allsupportskills.supportskill[i].supportskillcard[j].numTypeReq;k++){
                        cout << allsupportskills.supportskill[i].supportskillcard[j].types_needed[k].affiliation;

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
                cin >> list_on;

                if(!(cin.good()) || list_on!=1){
                    cin.clear();
                    cin.ignore(256, '\n');
                    list_on=0;
                }

            }while(list_on==1);
        }

}


void print_exact_profiles(ALL_Cards *all_cards){

    int i,j,k,l, affiliation_sum_tracker[MAXCHARACTERS], not_in_array=0, sum_size=0, current_sum;
    string filename, txt=".txt";
    ofstream myoutput;

    for(i=0;i<all_cards->number_of_characters;i++){
        not_in_array=0;

        for(j=0;j<sum_size;j++){
            if(all_cards->card[i].affiliation_sum!=affiliation_sum_tracker[j]){
                not_in_array++;
            }
        }

        if(not_in_array==sum_size){
            current_sum=all_cards->card[i].affiliation_sum;

            filename="Character Profiles/Exact Profiles/";
            filename.append(all_cards->card[i].cardtype[0].affiliation);

            for(k=1;k<all_cards->card[i].number_of_types;k++){
                filename.append("_");
                filename.append(all_cards->card[i].cardtype[k].affiliation);
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

            affiliation_sum_tracker[sum_size]=current_sum;
            sum_size++;
        }
    }

    cout << "\n\n\tExact Profiles Updated.\n\n";
}


void check_stats(ALL_Cards *all_cards, ALL_Cards *unique_cards, Affiliation_Array *affiliation_array, AllSupportSkills *allsupportskills){

    int choice, finished=0, affiliation_number=0, keep_adding=0, translator, i, new_search;

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

        cin >> choice;

        while(!(cin.good()) || choice>8 || choice<1){
            cin.clear();
            cin.ignore(256,'\n');
            cout << "Invalid choice. Please enter again: ";
            cin >> choice;
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
                        cin >> affiliation_number;

                        while(!(cin.good()) || affiliation_number<0){
                            cin.clear();
                            cin.ignore(256,'\n');
                            cout << "Invalid choice. Please enter again: ";
                            cin >> affiliation_number;
                        }

                        return_affiliation_numbers(all_cards, unique_cards, affiliation_number);
                    }else
                        if(choice==5){
                            cout << "\n";
                            for(i=0;i<affiliation_array->number_of_affiliations;i++){
                                cout << right << setw(2) << i+1 << ")" << left << setw(23) << affiliation_array->affiliation[i].aff_name << "  ";

                                if(i%5==4){
                                    cout << "\n";
                                }
                            }

                            keep_adding=0;

                            cout << "\n\n\nSelect which affiliation(s) (1-" << affiliation_array->number_of_affiliations << ") you wish to search, then press enter\nEnter 0 to start search:\n";

                            do{
                                cin>>translator;

                                if(!(cin.good()) || translator<0 || translator>affiliation_array->number_of_affiliations){
                                    cin.clear();
                                    cin.ignore(256,'\n');
                                    cout << "\n\tInvalid entry\n";
                                }else
                                    if(translator==0){
                                        break;
                                    }else{
                                        new_search=0;

                                        for(i=0;i<keep_adding;i++){
                                            if(aff_counter.affiliation[i].type_value!=affiliation_array->affiliation[translator-1].type_value){
                                                new_search++;
                                            }
                                        }

                                        if(new_search==keep_adding){
                                            strcpy(aff_counter.affiliation[keep_adding].aff_name,affiliation_array->affiliation[translator-1].aff_name);
                                            aff_counter.affiliation[keep_adding].type_value=affiliation_array->affiliation[translator-1].type_value;
                                            keep_adding++;
                                        }
                                    }

                                if(keep_adding==affiliation_array->number_of_affiliations){
                                    break;
                                }

                            }while(1==1);

                            aff_counter.number_of_affiliations=keep_adding;

                            cout << "\n";

                            count_affiliations(all_cards,unique_cards,&aff_counter);
                        }else
                            if(choice==6){
                                count_affiliation_spread(all_cards, unique_cards);
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

    }while(finished==1);

}


void print_info(AllSupportSkills allsupportskills, ALL_Cards all_cards){

    int x, i, counter, choice, rand_char, start, list_on=1;

    cout << "List (1) or random (2) or Quit (0)?: ";
    cin >> start;

    if(!(cin.good())){
        cin.clear();
        cin.ignore(256,'\n');
        start=0;
    }

    if(start==1){
        cout << endl;

        for(counter=0;counter<all_cards.number_of_characters;counter++){
            cout << all_cards.card[counter].rarity << "* " << all_cards.card[counter].name << " is afilliated with " << all_cards.card[counter].cardtype[0].affiliation;
                    if(all_cards.card[counter].number_of_types>1){
                        for(x=1;x<all_cards.card[counter].number_of_types;x++){
                            cout << " and " << all_cards.card[counter].cardtype[x].affiliation;
                        }
                    }
                    cout << ".\n";

                    if(all_cards.card[counter].has_skill==true){
                        cout << all_cards.card[counter].rarity << "* " << all_cards.card[counter].name << " has skill " << all_cards.card[counter].skillname << ", which requires:\n";
                        for(x=0;x<allsupportskills.supportskill[all_cards.card[counter].skill_ID].max_level;x++){
                            cout << "\t" << allsupportskills.supportskill[all_cards.card[counter].skill_ID].supportskillcard[all_cards.card[counter].skillcard_ID].supportskillreqs[x].typereq << " of ";
                            for(i=0;i<allsupportskills.supportskill[all_cards.card[counter].skill_ID].supportskillcard[all_cards.card[counter].skillcard_ID].numTypeReq;i++){
                                cout << "(" << allsupportskills.supportskill[all_cards.card[counter].skill_ID].supportskillcard[all_cards.card[counter].skillcard_ID].types_needed[i].affiliation << ")  ";
                            }
                            cout << " for level " <<  allsupportskills.supportskill[all_cards.card[counter].skill_ID].supportskillcard[all_cards.card[counter].skillcard_ID].supportskillreqs[x].level << endl;
                        }
                    }else{
                        cout << all_cards.card[counter].rarity << "* " << all_cards.card[counter].name << " does not have a skill.\n";
                    }
                    cout << all_cards.card[counter].rarity << "* " << all_cards.card[counter].name << " costs " << all_cards.card[counter].cost << " points.\n";

                cout << "Array ID: " << counter << endl << endl;

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

            do{
                rand_char=rand()%all_cards.number_of_characters;
                cout << "\n\n" << all_cards.card[rand_char].rarity << "* " << all_cards.card[rand_char].name << " is afilliated with " << all_cards.card[rand_char].cardtype[0].affiliation;
                    if(all_cards.card[rand_char].number_of_types>1){
                        for(x=1;x<all_cards.card[rand_char].number_of_types;x++){
                            cout << " and " << all_cards.card[rand_char].cardtype[x].affiliation;
                        }
                    }
                    cout << ".\n";

                    if(all_cards.card[rand_char].has_skill==true){
                        cout << all_cards.card[rand_char].rarity << "* " << all_cards.card[rand_char].name << " has skill " << all_cards.card[rand_char].skillname << ", which requires:\n";
                        for(x=0;x<allsupportskills.supportskill[all_cards.card[rand_char].skill_ID].max_level;x++){
                            cout << "\t" << allsupportskills.supportskill[all_cards.card[rand_char].skill_ID].supportskillcard[all_cards.card[rand_char].skillcard_ID].supportskillreqs[x].typereq << " of ";
                            for(i=0;i<allsupportskills.supportskill[all_cards.card[rand_char].skill_ID].supportskillcard[all_cards.card[rand_char].skillcard_ID].numTypeReq;i++){
                                cout << "(" << allsupportskills.supportskill[all_cards.card[rand_char].skill_ID].supportskillcard[all_cards.card[rand_char].skillcard_ID].types_needed[i].affiliation << ")  ";
                            }
                            cout << " for level " <<  allsupportskills.supportskill[all_cards.card[rand_char].skill_ID].supportskillcard[all_cards.card[rand_char].skillcard_ID].supportskillreqs[x].level << endl;
                        }
                    }else{
                        cout << all_cards.card[rand_char].rarity << "* " << all_cards.card[rand_char].name << " does not have a skill.\n";
                    }
                    cout << all_cards.card[rand_char].rarity << "* " << all_cards.card[rand_char].name << " costs " << all_cards.card[rand_char].cost << " points.\n";

                cout << "Array ID: " << rand_char << endl;
                cout << "\n\nRun again? (Yes = 1):  ";
                cin >> choice;
                if(choice!=1){
                    cin.clear();
                    cin.ignore(256,'\n');
                    choice=0;
                }
                cout << "\n\n";

            }while(choice==1);
        }

    }
