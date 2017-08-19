using namespace std;

#include "classes.h"

/**
    This is the main function of my support deck solver. From here you may enter into three different functions:
        1) Brute force support deck combination solver
        2) Statistics analysis
        3) Print to screen info about cards
**/

int main(){


    int x,i, z=0, get_skill, new_search, translator, keep_adding;
    string numText;
    int path, is_double=0, wants_max_cost=0, user_max_cost;
    bool still_in_use=true, continue_with_solving, dataBaseSuccessful=false;
    ifstream myfile;

    //the following four functions create the data used by the program
    cout << "Creating database . . .\n\n";
    dataBaseSuccessful=create_Database(&allsupportskills, &all_cards, &unique_affiliations, &affiliation_array);

    if(dataBaseSuccessful){
        //check if any new profiles exist
        cout << "\nChecking for new profiles . . .\n\n";
        checkForNewProfiles(&unique_affiliations);

        do{
            cout << "\nCheck combinations (1) or check stats (2) or print profile info (3) or Quit (0)? :  ";
            cin >> numText;

            path=StringToInt(numText);

            if(path==1){
                reset_support_deck(&supportdeck);

                cout << "\n\nHow many skills (2 - 6) do you want in your support deck?: ";
                cin >> numText;
                supportdeck.number_of_skills=StringToInt(numText);

                while(supportdeck.number_of_skills>6 || supportdeck.number_of_skills<2){
                    cin.clear();
                    cin.ignore(256, '\n');
                    cout << "Please enter a number from 2 to 6: ";
                    cin >> numText;
                    supportdeck.number_of_skills=StringToInt(numText);
                }

                cout << "\n\nHow many total cards (" << supportdeck.number_of_skills << " - " << SUPPORTDECK << ") do you want in your support deck?: ";
                cin >> numText;
                supportdeck.total_cards_to_use=StringToInt(numText);

                while(supportdeck.total_cards_to_use>SUPPORTDECK || supportdeck.total_cards_to_use<supportdeck.number_of_skills){
                    cin.clear();
                    cin.ignore(256, '\n');
                    cout << "Please enter a number from " << supportdeck.number_of_skills << " to " << SUPPORTDECK << ": ";
                    cin >> numText;
                    supportdeck.total_cards_to_use=StringToInt(numText);
                }

                cout << "\n\nSet a maximum cap cost? (Yes = 1): ";
                cin >> numText;
                wants_max_cost=StringToInt(numText);

                if(wants_max_cost==1){
                    cout << "\n\tEnter the desired maximum cap cost (not less than zero):  ";
                    cin >> numText;
                    user_max_cost=StringToInt(numText);

                    while(user_max_cost<0){
                        cin.clear();
                        cin.ignore(256, '\n');
                        cout << "\n\n\tInvalid entry.";
                        cout << "\n\tEnter the desired maximum cap cost (not less than zero):  ";
                        cin >> numText;
                        user_max_cost=StringToInt(numText);
                    }

                    supportdeck.user_set_max_cost=user_max_cost;
                    supportdeck.max_cost_set=true;
                }

                if(supportdeck.number_of_skills>1){
                    cout << "\n\nEnforce minimum skill levels? (Yes = 1): ";
                    cin >> numText;
                    supportdeck.looking_for_specific_level=StringToInt(numText);
                    if(supportdeck.looking_for_specific_level!=1){
                        supportdeck.looking_for_specific_level=0;
                    }

                    cout << "\n";

                    for(z=0;z<allsupportskills.numberOfSkills;z++){
                        cout << z+1 << ") " << allsupportskills.supportskill[z].skillName << endl;
                    }
                    cout << "\n\n";

                    for(x=0;x<supportdeck.number_of_skills;x++){
                        do{
                            cout << "Please choose a skill: ";
                            cin >> numText;
                            get_skill=StringToInt(numText);

                            if(get_skill>allsupportskills.numberOfSkills || get_skill<1){
                                cout << "\n\tPlease enter a number from 1 to " << allsupportskills.numberOfSkills << endl << endl;
                            }

                            if(get_skill<=allsupportskills.numberOfSkills){
                                is_double=0;

                                for(i=0;i<x;i++){
                                    if(get_skill-1==supportdeck.skill_locator[i]){
                                        is_double=1;
                                    }
                                }

                                if(is_double==1){
                                    cout << "\n\tSkill already chosen - choose a different one.\n\n";
                                }
                            }

                        }while(get_skill>allsupportskills.numberOfSkills || get_skill<1 || is_double==1);

                        supportdeck.skills_in_deck[x]=allsupportskills.supportskill[get_skill-1].skillName;
                        supportdeck.skill_locator[x]=get_skill-1;

                        for(i=0;i<allsupportskills.supportskill[get_skill-1].numberOfCards;i++){
                            cout << i+1 << ") " << allsupportskills.supportskill[get_skill-1].supportskillcard[i].rarity << "* " << allsupportskills.supportskill[get_skill-1].supportskillcard[i].charactername << "\n";
                        }

                        cout << "\nIgnore any skill cards? Enter the index of those you don't want to search - enter 0 when ready to proceed:  ";

                        keep_adding=0;

                        do{
                            cin>>numText;
                            translator=StringToInt(numText);

                            if(translator<0 || translator>allsupportskills.supportskill[get_skill-1].numberOfCards){
                                cin.clear();
                                cin.ignore(256,'\n');
                                cout << "\n\tInvalid entry\n";
                            }else
                                if(translator==0){
                                    break;
                                }else{
                                    new_search=0;

                                    for(i=0;i<keep_adding;i++){
                                        if(supportdeck.ignore_list[x][i]!=(translator-1)){
                                            new_search++;
                                        }
                                    }

                                    if(new_search==keep_adding){
                                        supportdeck.ignore_list[x][keep_adding]=translator-1;
                                        keep_adding++;
                                    }
                                }

                            if(keep_adding == (allsupportskills.supportskill[get_skill-1].numberOfCards-1) ){
                                break;
                            }

                        }while(1==1);

                        supportdeck.num_ignored_cards[x]=keep_adding;
                        supportdeck.num_allowed_cards[x]=allsupportskills.supportskill[get_skill-1].numberOfCards-keep_adding;

                        if(supportdeck.looking_for_specific_level){
                            if(allsupportskills.supportskill[get_skill-1].max_level==1){
                                supportdeck.skill_threshold[x]=1;
                            }else{
                                cout << "\nSet minimum skill level (";
                                for(z=0;z<allsupportskills.supportskill[get_skill-1].max_level;z++){
                                    cout << z+1;

                                    if(z+1<allsupportskills.supportskill[get_skill-1].max_level){
                                        cout << ", ";
                                    }else{
                                        cout << "): ";
                                    }
                                }

                                cin >> numText;
                                supportdeck.skill_threshold[x]=StringToInt(numText);

                                while(supportdeck.skill_threshold[x]>allsupportskills.supportskill[get_skill-1].max_level || supportdeck.skill_threshold[x]<1){
                                    cout << "\nInvalid value. Enter again: ";
                                    cin.clear();
                                    cin.ignore(256, '\n');
                                    cin >> numText;
                                    supportdeck.skill_threshold[x]=StringToInt(numText);
                                }
                            }

                        }else{
                            supportdeck.skill_threshold[x]=1;
                        }
                        cout << "\n\n";
                    }

                    continue_with_solving=true;

                    if(checkIfFileExists(&supportdeck,&allsupportskills)){
                        cout << "\n\nA file containing combinations for these skills already exists.";
                        cout << "\nRunning the solver will overwrite the exisiting file.";
                        cout << "\n\n\tContinue with solving? (Yes = 1):  ";
                        cin >> numText;
                        if(StringToInt(numText)!=1){
                            continue_with_solving=false;
                        }

                    if(continue_with_solving){
                        if(supportdeck.total_cards_to_use>supportdeck.number_of_skills){
                            cout << "Enter the minimum number of matching types per card: ";
                            cin >> numText;
                            supportdeck.type_threshold=StringToInt(numText);

                            while(supportdeck.type_threshold<0){
                                cout << "\nInvalid value. Enter again: ";
                                cin.clear();
                                cin.ignore(256, '\n');
                                cin >> numText;
                                supportdeck.type_threshold=StringToInt(numText);
                            }

                            cout << "\n\nQuery through which rarity (5 4 3 2 1)? : ";
                            cin >> numText;
                            supportdeck.using_rarity=StringToInt(numText);

                            if( supportdeck.using_rarity<1 || supportdeck.using_rarity>5){
                                cin.clear();
                                cin.ignore(256, '\n');
                                supportdeck.using_rarity=4;
                            }
                        }

                        cout << "\n\nStop searching after a certain number of solutions? (Yes = 1):  ";
                        cin >> numText;
                        supportdeck.breaking_early=StringToInt(numText);

                        if(supportdeck.breaking_early!=1){
                            cin.clear();
                            cin.ignore(256, '\n');
                            supportdeck.breaking_early=0;
                            supportdeck.breaking_at_solution=0;
                        }else{
                            cout << "\n\tSearch for how many solutions?:  ";
                            cin >> numText;
                            supportdeck.breaking_at_solution=StringToInt(numText);

                            while(!(cin.good()) || supportdeck.breaking_at_solution<1){
                                cout << "\nInvalid value. Enter again: ";
                                cin.clear();
                                cin.ignore(256, '\n');
                                cin >> numText;
                                supportdeck.breaking_at_solution=StringToInt(numText);
                            }
                        }

                        construct_support_deck(&supportdeck, &allsupportskills, &all_cards, &unique_affiliations);

                    }

                }else{
                    cout << "\n\n\t\tThanks for using the support skill optimizer!!";
                }
                }
            }else
                if(path==2){
                    check_stats(&all_cards,&unique_affiliations,&affiliation_array, &allsupportskills);
                }else
                    if(path==3){
                        print_info(&allsupportskills,&all_cards);
                    }else
                        if(path==0){
                            still_in_use=false;
                        }

            if(path!=0){
                cout << "\n\n\n\t\tDo something else? (Yes = 1): ";
                cin >>still_in_use;

                if( !(cin.good())){
                    cin.clear();
                    cin.ignore(256, '\n');
                    still_in_use=false;
                }
            }

            cout << "\n\n";

        }while(still_in_use);
    }else{
        cout << "\n\nPress enter to exit";
        getchar();
    }

    cout << "\n\n";

    return 0;
}
