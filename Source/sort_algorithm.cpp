using namespace std;

#include "declarations.h"
#include "classes.h"

/**
    This is the combination solver component. The user selects all their search options in main - these options are stored in the
    "Support Deck" structure and called when needed. This function receives the address of each other structure in the program:
    "allsupportskills", "all_cards", and "unique_affiliations", as well as an integer representing how far into unique_affiliations
    the program should search (rarity constraint).

    This fuction can solve as little as two skill decks or as many as six skill decks. Before the function breaks into the
    individual search paths, it creates two text files, which are named based on the skills chosen. The program will store the
    results it finds in these text files. Next it runs the function "filter_allowed_skill_cards", which creates an array holding
    the ID's of the user chosen skill cards to search for each skill. At that point it breaks into the designated path.

    Each path does three things:
        1) notate the ID's of the skill cards being used in this run
        2) run a presearch configuration (function "presearch_config")
            -This function performs four tasks:
                i)  prints to screen the names of the skill cards for which it is currently solving combinations
                ii) enter the ID's of the skill cards into an array
                iii) record the total number of affiliations needed for the current combination of skill cards
                iv) filter out the unique profiles which do not meet the type threshold requirement and record the number
                    of cards that do meet the type threshold
            -After these tasks are completed, the path continues on its search
        3) enter the ID's of the unique profiles used into an array

**/

void construct_support_deck(SupportDeck *supportdeck, AllSupportSkills *allsupportskills, ALL_Cards *all_cards, ALL_Cards *unique_affiliations){

    int i=0,k,x,y,z,m,n,j, effective_chars=0, numChars=0, entry_counter=0, base_entry_counter=0;
    int support_array[SUPPORTDECK], skill_card_locator[SUPPORTDECK], entry_tracker[MAXSUPPORTCARDS];
    int allowed_skill_cards[SUPPORTDECK][MAXSUPPORTCARDS];
    vector<int> unique_profile_match;
    double time_start=time(0), time_end, run_start, run_end;
    ofstream myoutput, baseoutput;
    string filename="", base_filename="";

    filename=nameFile(supportdeck,allsupportskills,true);
    base_filename=nameFile(supportdeck,allsupportskills,false);

    for(i=0;i<unique_affiliations->number_of_characters;i++){
        if(unique_affiliations->card[i].rarity>=supportdeck->using_rarity){
            effective_chars++;
        }
    }


    myoutput.open(filename.c_str());
    baseoutput.open(base_filename.c_str());

    if(myoutput.is_open() && baseoutput.is_open()){

        supportdeck->solution_threshold_reached=false;

        for(j=0;j<allsupportskills->supportskill[supportdeck->skill_locator[0]].numberOfCards;j++){
            entry_tracker[j]=0;
        }

        filter_allowed_skill_cards(supportdeck, allsupportskills, allowed_skill_cards);

        if(supportdeck->number_of_skills==2){

            for(i=0;i<supportdeck->num_allowed_cards[0];i++){
                run_start=time(0);
                skill_card_locator[0]=allowed_skill_cards[0][i];

                for(m=0;m<supportdeck->num_allowed_cards[1];m++){
                    skill_card_locator[1]=allowed_skill_cards[1][m];

                    presearch_config(allsupportskills, unique_affiliations, supportdeck, skill_card_locator, effective_chars, &unique_profile_match, numChars);

                    for(j=0;j<supportdeck->number_of_skills;j++){
                        support_array[j]=supportdeck->card_locator[j];
                    }

                    if(!willUseCardSlot(supportdeck->total_cards_to_use,supportdeck->number_of_skills+1)){
                        find_combinations(supportdeck, all_cards, unique_affiliations, allsupportskills, support_array, skill_card_locator, entry_counter, base_entry_counter, entry_tracker, i, myoutput, baseoutput);

                        if(supportdeck->solution_threshold_reached){
                            goto solution_threshold_reached;
                        }
                    }

                    for(k=0;k<numChars*willUseCardSlot(supportdeck->total_cards_to_use,3);k++){
                        support_array[2]=unique_profile_match[k];

                        if(!willUseCardSlot(supportdeck->total_cards_to_use,supportdeck->number_of_skills+2)){
                            find_combinations(supportdeck, all_cards, unique_affiliations, allsupportskills, support_array, skill_card_locator, entry_counter, base_entry_counter, entry_tracker, i, myoutput, baseoutput);

                            if(supportdeck->solution_threshold_reached){
                                goto solution_threshold_reached;
                            }
                        }

                        for(x=k;x<numChars*willUseCardSlot(supportdeck->total_cards_to_use,4);x++){
                            support_array[3]=unique_profile_match[x];

                            if(!willUseCardSlot(supportdeck->total_cards_to_use,supportdeck->number_of_skills+3)){
                                find_combinations(supportdeck, all_cards, unique_affiliations, allsupportskills, support_array, skill_card_locator, entry_counter, base_entry_counter, entry_tracker, i, myoutput, baseoutput);

                                if(supportdeck->solution_threshold_reached){
                                    goto solution_threshold_reached;
                                }
                            }

                            for(y=x;y<numChars*willUseCardSlot(supportdeck->total_cards_to_use,5);y++){
                                support_array[4]=unique_profile_match[y];

                                if(!willUseCardSlot(supportdeck->total_cards_to_use,supportdeck->number_of_skills+4)){
                                    find_combinations(supportdeck, all_cards, unique_affiliations, allsupportskills, support_array, skill_card_locator, entry_counter, base_entry_counter, entry_tracker, i, myoutput, baseoutput);

                                    if(supportdeck->solution_threshold_reached){
                                        goto solution_threshold_reached;
                                    }
                                }

                                for(z=y;z<numChars*willUseCardSlot(supportdeck->total_cards_to_use,6);z++){
                                    support_array[5]=unique_profile_match[z];

                                    if(!willUseCardSlot(supportdeck->total_cards_to_use,supportdeck->number_of_skills+5)){
                                        find_combinations(supportdeck, all_cards, unique_affiliations, allsupportskills, support_array, skill_card_locator, entry_counter, base_entry_counter, entry_tracker, i, myoutput, baseoutput);

                                        if(supportdeck->solution_threshold_reached){
                                            goto solution_threshold_reached;
                                        }
                                    }

                                    for(n=z;n<numChars*willUseCardSlot(supportdeck->total_cards_to_use,7);n++){
                                        support_array[6]=unique_profile_match[n];

                                        find_combinations(supportdeck, all_cards, unique_affiliations, allsupportskills, support_array, skill_card_locator, entry_counter, base_entry_counter, entry_tracker, i, myoutput, baseoutput);

                                        if(supportdeck->solution_threshold_reached){
                                            goto solution_threshold_reached;
                                        }

                                    } //end of n iteration (fifth card)

                                }  //end of z iteration (first card)

                            } // end of y iteration (second card)

                        } //end of x iteration (third card)

                    } //end of k iteration (fourth card)

                } //end of m iteration (second support skill)
                run_end=time(0);

                print_endround_info(run_start, run_end, entry_tracker, i);

            }//end of i iteration (first support skill)

        }else
            if(supportdeck->number_of_skills==3){

                for(i=0;i<supportdeck->num_allowed_cards[0];i++){
                    run_start=time(0);
                    skill_card_locator[0]=allowed_skill_cards[0][i];

                    for(m=0;m<supportdeck->num_allowed_cards[1];m++){
                        skill_card_locator[1]=allowed_skill_cards[1][m];

                        for(n=0;n<supportdeck->num_allowed_cards[2];n++){
                            skill_card_locator[2]=allowed_skill_cards[2][n];

                            presearch_config(allsupportskills, unique_affiliations, supportdeck, skill_card_locator, effective_chars, &unique_profile_match, numChars);

                            for(j=0;j<supportdeck->number_of_skills;j++){
                                support_array[j]=supportdeck->card_locator[j];
                            }

                            if(!willUseCardSlot(supportdeck->total_cards_to_use,supportdeck->number_of_skills+1)){
                                find_combinations(supportdeck, all_cards, unique_affiliations, allsupportskills, support_array, skill_card_locator, entry_counter, base_entry_counter, entry_tracker, i, myoutput, baseoutput);

                                if(supportdeck->solution_threshold_reached){
                                    goto solution_threshold_reached;
                                }
                            }

                            for(k=0;k<numChars*willUseCardSlot(supportdeck->total_cards_to_use,supportdeck->number_of_skills+1);k++){
                                support_array[3]=unique_profile_match[k];

                                if(!willUseCardSlot(supportdeck->total_cards_to_use,supportdeck->number_of_skills+2)){
                                    find_combinations(supportdeck, all_cards, unique_affiliations, allsupportskills, support_array, skill_card_locator, entry_counter, base_entry_counter, entry_tracker, i, myoutput, baseoutput);

                                    if(supportdeck->solution_threshold_reached){
                                        goto solution_threshold_reached;
                                    }
                                }

                                for(x=k;x<numChars*willUseCardSlot(supportdeck->total_cards_to_use,supportdeck->number_of_skills+2);x++){
                                    support_array[4]=unique_profile_match[x];

                                    if(!willUseCardSlot(supportdeck->total_cards_to_use,supportdeck->number_of_skills+3)){
                                        find_combinations(supportdeck, all_cards, unique_affiliations, allsupportskills, support_array, skill_card_locator, entry_counter, base_entry_counter, entry_tracker, i, myoutput, baseoutput);

                                        if(supportdeck->solution_threshold_reached){
                                            goto solution_threshold_reached;
                                        }
                                    }

                                    for(y=x;y<numChars*willUseCardSlot(supportdeck->total_cards_to_use,supportdeck->number_of_skills+3);y++){
                                        support_array[5]=unique_profile_match[y];

                                        if(!willUseCardSlot(supportdeck->total_cards_to_use,supportdeck->number_of_skills+4)){
                                            find_combinations(supportdeck, all_cards, unique_affiliations, allsupportskills, support_array, skill_card_locator, entry_counter, base_entry_counter, entry_tracker, i, myoutput, baseoutput);

                                            if(supportdeck->solution_threshold_reached){
                                                goto solution_threshold_reached;
                                            }
                                        }

                                        for(z=y;z<numChars*willUseCardSlot(supportdeck->total_cards_to_use,supportdeck->number_of_skills+4);z++){
                                            support_array[6]=unique_profile_match[z];

                                            find_combinations(supportdeck, all_cards, unique_affiliations, allsupportskills, support_array, skill_card_locator, entry_counter, base_entry_counter, entry_tracker, i, myoutput, baseoutput);

                                            if(supportdeck->solution_threshold_reached){
                                                goto solution_threshold_reached;
                                            }

                                        }  //end of z iteration (first card)

                                    } // end of y iteration (second card)

                                } //end of x iteration (third card)

                            } //end of k iteration (fourth card)

                        } //end of n iteration (third support skill)

                    } //end of m iteration (second support skill)
                    run_end=time(0);

                    print_endround_info(run_start, run_end, entry_tracker, i);


                }//end of i iteration (first support skill)

            }else
                if(supportdeck->number_of_skills==4){

                    for(i=0;i<supportdeck->num_allowed_cards[0];i++){
                        run_start=time(0);
                        skill_card_locator[0]=allowed_skill_cards[0][i];

                        for(m=0;m<supportdeck->num_allowed_cards[1];m++){
                            skill_card_locator[1]=allowed_skill_cards[1][m];

                            for(n=0;n<supportdeck->num_allowed_cards[2];n++){
                                skill_card_locator[2]=allowed_skill_cards[2][n];

                                for(z=0;z<supportdeck->num_allowed_cards[3];z++){
                                    skill_card_locator[3]=allowed_skill_cards[3][z];

                                    presearch_config(allsupportskills, unique_affiliations, supportdeck, skill_card_locator, effective_chars, &unique_profile_match, numChars);

                                    for(j=0;j<supportdeck->number_of_skills;j++){
                                        support_array[j]=supportdeck->card_locator[j];
                                    }

                                    if(!willUseCardSlot(supportdeck->total_cards_to_use,supportdeck->number_of_skills+1)){
                                        find_combinations(supportdeck, all_cards, unique_affiliations, allsupportskills, support_array, skill_card_locator, entry_counter, base_entry_counter, entry_tracker, i, myoutput, baseoutput);

                                        if(supportdeck->solution_threshold_reached){
                                            goto solution_threshold_reached;
                                        }
                                    }

                                    for(k=0;k<numChars*willUseCardSlot(supportdeck->total_cards_to_use,supportdeck->number_of_skills+1);k++){
                                        support_array[4]=unique_profile_match[k];

                                        if(!willUseCardSlot(supportdeck->total_cards_to_use,supportdeck->number_of_skills+2)){
                                            find_combinations(supportdeck, all_cards, unique_affiliations, allsupportskills, support_array, skill_card_locator, entry_counter, base_entry_counter, entry_tracker, i, myoutput, baseoutput);

                                            if(supportdeck->solution_threshold_reached){
                                                goto solution_threshold_reached;
                                            }
                                        }

                                        for(x=k;x<numChars*willUseCardSlot(supportdeck->total_cards_to_use,supportdeck->number_of_skills+2);x++){
                                            support_array[5]=unique_profile_match[x];

                                            if(!willUseCardSlot(supportdeck->total_cards_to_use,supportdeck->number_of_skills+3)){
                                                find_combinations(supportdeck, all_cards, unique_affiliations, allsupportskills, support_array, skill_card_locator, entry_counter, base_entry_counter, entry_tracker, i, myoutput, baseoutput);

                                                if(supportdeck->solution_threshold_reached){
                                                    goto solution_threshold_reached;
                                                }
                                            }

                                            for(y=x;y<numChars*willUseCardSlot(supportdeck->total_cards_to_use,supportdeck->number_of_skills+3);y++){
                                                support_array[6]=unique_profile_match[y];

                                                find_combinations(supportdeck, all_cards, unique_affiliations, allsupportskills, support_array, skill_card_locator, entry_counter, base_entry_counter, entry_tracker, i, myoutput, baseoutput);

                                                if(supportdeck->solution_threshold_reached){
                                                    goto solution_threshold_reached;
                                                }

                                            } // end of y iteration (first card)

                                        } //end of x iteration (second card)

                                    } //end of k iteration (third card)

                                } //end of z iteration (fourth support skill)

                            } //end of n iteration (third support skill)

                        } //end of m iteration (second support skill)

                        run_end=time(0);

                        print_endround_info(run_start, run_end, entry_tracker, i);

                    }//end of i iteration (first support skill)


                }else
                    if(supportdeck->number_of_skills==5){

                        for(i=0;i<supportdeck->num_allowed_cards[0];i++){
                            run_start=time(0);
                            skill_card_locator[0]=allowed_skill_cards[0][i];

                            for(m=0;m<supportdeck->num_allowed_cards[1];m++){
                                skill_card_locator[1]=allowed_skill_cards[1][m];

                                for(n=0;n<supportdeck->num_allowed_cards[2];n++){
                                    skill_card_locator[2]=allowed_skill_cards[2][n];

                                    for(z=0;z<supportdeck->num_allowed_cards[3];z++){
                                        skill_card_locator[3]=allowed_skill_cards[3][z];

                                        for(y=0;y<supportdeck->num_allowed_cards[4];y++){
                                            skill_card_locator[4]=allowed_skill_cards[4][y];

                                            presearch_config(allsupportskills, unique_affiliations, supportdeck, skill_card_locator, effective_chars, &unique_profile_match, numChars);

                                            for(j=0;j<supportdeck->number_of_skills;j++){
                                                support_array[j]=supportdeck->card_locator[j];
                                            }

                                            if(!willUseCardSlot(supportdeck->total_cards_to_use,supportdeck->number_of_skills+1)){
                                                find_combinations(supportdeck, all_cards, unique_affiliations, allsupportskills, support_array, skill_card_locator, entry_counter, base_entry_counter, entry_tracker, i, myoutput, baseoutput);

                                                if(supportdeck->solution_threshold_reached){
                                                    goto solution_threshold_reached;
                                                }
                                            }

                                            for(k=0;k<numChars*willUseCardSlot(supportdeck->total_cards_to_use,supportdeck->number_of_skills+1);k++){
                                                support_array[5]=unique_profile_match[k];

                                                if(!willUseCardSlot(supportdeck->total_cards_to_use,supportdeck->number_of_skills+2)){
                                                    find_combinations(supportdeck, all_cards, unique_affiliations, allsupportskills, support_array, skill_card_locator, entry_counter, base_entry_counter, entry_tracker, i, myoutput, baseoutput);

                                                    if(supportdeck->solution_threshold_reached){
                                                        goto solution_threshold_reached;
                                                    }
                                                }

                                                for(x=k;x<numChars*willUseCardSlot(supportdeck->total_cards_to_use,supportdeck->number_of_skills+2);x++){
                                                    support_array[6]=unique_profile_match[x];

                                                    find_combinations(supportdeck, all_cards, unique_affiliations, allsupportskills, support_array, skill_card_locator, entry_counter, base_entry_counter, entry_tracker, i, myoutput, baseoutput);

                                                    if(supportdeck->solution_threshold_reached){
                                                        goto solution_threshold_reached;
                                                    }

                                                } //end of x iteration (first card)

                                            } //end of k iteration (second card)

                                        } //end of y iteration (fifth support skill)

                                    } //end of z iteration (fourth support skill)

                                } //end of n iteration (third support skill)

                            } //end of m iteration (second support skill)

                            run_end=time(0);

                            print_endround_info(run_start, run_end, entry_tracker, i);

                        }//end of i iteration (first support skill)

                    }else
                        if(supportdeck->number_of_skills==6){

                            for(i=0;i<supportdeck->num_allowed_cards[0];i++){
                                run_start=time(0);
                                skill_card_locator[0]=allowed_skill_cards[0][i];

                                for(m=0;m<supportdeck->num_allowed_cards[1];m++){
                                    skill_card_locator[1]=allowed_skill_cards[1][m];

                                    for(n=0;n<supportdeck->num_allowed_cards[2];n++){
                                        skill_card_locator[2]=allowed_skill_cards[2][n];

                                        for(z=0;z<supportdeck->num_allowed_cards[3];z++){
                                            skill_card_locator[3]=allowed_skill_cards[3][z];

                                            for(y=0;y<supportdeck->num_allowed_cards[4];y++){
                                                skill_card_locator[4]=allowed_skill_cards[4][y];

                                                for(x=0;x<supportdeck->num_allowed_cards[5];x++){
                                                    skill_card_locator[5]=allowed_skill_cards[5][x];

                                                    presearch_config(allsupportskills, unique_affiliations, supportdeck, skill_card_locator, effective_chars, &unique_profile_match, numChars);

                                                    for(j=0;j<supportdeck->number_of_skills;j++){
                                                        support_array[j]=supportdeck->card_locator[j];
                                                    }

                                                    if(!willUseCardSlot(supportdeck->total_cards_to_use,supportdeck->number_of_skills+1)){
                                                        find_combinations(supportdeck, all_cards, unique_affiliations, allsupportskills, support_array, skill_card_locator, entry_counter, base_entry_counter, entry_tracker, i, myoutput, baseoutput);

                                                        if(supportdeck->solution_threshold_reached){
                                                            goto solution_threshold_reached;
                                                        }
                                                    }

                                                    for(k=0;k<numChars*willUseCardSlot(supportdeck->total_cards_to_use,supportdeck->number_of_skills+1);k++){
                                                        support_array[6]=unique_profile_match[k];

                                                        find_combinations(supportdeck, all_cards, unique_affiliations, allsupportskills, support_array, skill_card_locator, entry_counter, base_entry_counter, entry_tracker, i, myoutput, baseoutput);

                                                        if(supportdeck->solution_threshold_reached){
                                                            goto solution_threshold_reached;
                                                        }

                                                    } //end of k iteration (second card)

                                                } //end of q iteration (sixth support skill)

                                            } //end of y iteration (fifth support skill)

                                        } //end of z iteration (fourth support skill)

                                    } //end of n iteration (third support skill)

                                } //end of m iteration (second support skill)
                                run_end=time(0);

                                print_endround_info(run_start, run_end, entry_tracker, i);

                            }//end of i iteration (first support skill)

                        }

        solution_threshold_reached:;

        myoutput << "\n\n\tFound " << entry_counter << " emax/awakened only combinations!";
        baseoutput << "\n\n\tFound " << base_entry_counter << " base card only combinations!";

        myoutput.close();
        baseoutput.close();
    }

    if(entry_counter+base_entry_counter==0){
            cout << "\tNo results found for:\n";
            for(i=0;i<supportdeck->number_of_skills;i++){
                cout << "\t\t" << allsupportskills->supportskill[supportdeck->skill_locator[i]].skillName;
                cout << ", level " << supportdeck->skill_threshold[i] << "\n";
            }
            cout << "\tusing " << supportdeck->total_cards_to_use << " total cards with " << supportdeck->type_threshold << " matching types.\n";

            trackNoCombinations(supportdeck, allsupportskills);
        }else{
            cout << "\n\tFound " << entry_counter+base_entry_counter << " total solutions, " << entry_counter << " emax/awakened and " << base_entry_counter << " base solutions";
        }

        cout << "\n\n";

    time_end=time(0);

    if(difftime(time_end,time_start)>=60){
        cout << "Total run time: " << difftime(time_end,time_start)/60 << " minutes\n";
    }else{
        cout << "Total run time: " << difftime(time_end,time_start) << " seconds\n";
    }

    deleteIfEmptyFile(myoutput,filename,entry_counter);
    deleteIfEmptyFile(baseoutput,base_filename,base_entry_counter);

}
