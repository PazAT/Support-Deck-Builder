using namespace std;

#include "declarations.h"
#include "classes.h"

AllSupportSkills allsupportskills;
SupportSkill supportskill;
SupportSkillCard supportskillcard;
SupportSkillReqs supportskillreqs;
Affiliation affiliation;
Affiliation_Array affiliation_array;
Affiliation_Array aff_counter;
CardType cardtype;
Card card;
ALL_Cards all_cards;
ALL_Cards unique_affiliations;
SupportDeck supportdeck;

void create_supportCards(AllSupportSkills* allsupportskills, ALL_Cards* all_cards, ALL_Cards* unique_affiliations, Affiliation_Array* affiliation_array){

    int x,y,z, none_counter=0, is_not_same_aff=0;
    string placeholder, placeholder1, placeholder2, placeholder3, placeholder4;
    ifstream myfile;

    allsupportskills->numberOfSkills=0;
    affiliation_array->number_of_affiliations=0;

    myfile.open("Data/supportSkills.txt");

    if(myfile.is_open()){
        do{
            getline(myfile,placeholder1,'\n');
            char *charholder = new char[placeholder1.length()+1];
            strcpy(charholder, placeholder1.c_str());
            strcpy(allsupportskills->supportskill[allsupportskills->numberOfSkills].skillName, charholder);
            delete charholder;

            getline(myfile,placeholder1,'\n');
            char *charholder_2 = new char[placeholder1.length()+1];
            strcpy(charholder_2, placeholder1.c_str());
            strcpy(allsupportskills->supportskill[allsupportskills->numberOfSkills].skillNickname, charholder_2);
            delete charholder_2;

            allsupportskills->supportskill[allsupportskills->numberOfSkills].skill_ID=allsupportskills->numberOfSkills;

            allsupportskills->numberOfSkills++;

        }while( !(myfile.eof()) );
    }

    myfile.close();

    myfile.open("Data/supportSkillLevels.txt");

    if(myfile.is_open()==true){
        for(x=0;x<allsupportskills->numberOfSkills;x++){
            myfile >> allsupportskills->supportskill[x].max_level >> allsupportskills->supportskill[x].numberOfCards;
            for(y=0;y<allsupportskills->supportskill[x].numberOfCards;y++){
                allsupportskills->supportskill[x].supportskillcard[y].skillcard_ID=y;
                for(z=0;z<allsupportskills->supportskill[x].max_level;z++){
                    allsupportskills->supportskill[x].supportskillcard[y].supportskillreqs[z].level=z+1;
                    myfile >> allsupportskills->supportskill[x].supportskillcard[y].supportskillreqs[z].typereq;
                }
                myfile >> allsupportskills->supportskill[x].supportskillcard[y].rarity;
            }

        }
    }

    myfile.close();

    myfile.open("Data/supportCards.txt");

    if(myfile.is_open()){
        for(y=0;y<allsupportskills->numberOfSkills;y++){
            for(x=0;x<allsupportskills->supportskill[y].numberOfCards;x++){
                getline(myfile, placeholder1, ',');
                char *charholder1 = new char[placeholder1.length()+1];
                getline(myfile, placeholder2, ',');
                char *charholder2 = new char[placeholder2.length()+1];
                getline(myfile, placeholder3, ',');
                char *charholder3 = new char[placeholder3.length()+1];
                getline(myfile, placeholder4, '\n');
                char *charholder4 = new char[placeholder4.length()+1];

                strcpy(charholder1,placeholder1.c_str());
                strcpy(charholder2,placeholder2.c_str());
                strcpy(charholder3,placeholder3.c_str());
                strcpy(charholder4,placeholder4.c_str());

                strcpy(allsupportskills->supportskill[y].supportskillcard[x].charactername, charholder1);
                strcpy(allsupportskills->supportskill[y].supportskillcard[x].types_needed[0].affiliation, charholder2);
                strcpy(allsupportskills->supportskill[y].supportskillcard[x].types_needed[1].affiliation, charholder3);
                strcpy(allsupportskills->supportskill[y].supportskillcard[x].types_needed[2].affiliation, charholder4);

                none_counter=0;
                for(z=0;z<3;z++){
                    if(strcmp(allsupportskills->supportskill[y].supportskillcard[x].types_needed[z].affiliation,"None")!=0){
                        none_counter++;
                    }
                }
                allsupportskills->supportskill[y].supportskillcard[x].numTypeReq=none_counter;

                delete charholder1;
                delete charholder2;
                delete charholder3;
                delete charholder4;
            }

        }
    }

    myfile.close();

    myfile.open("Data/cardTypes.txt");

    if(myfile.is_open()){
        do{
            getline(myfile, placeholder, '\n');
            char *charholder = new char[placeholder.length()+1];
            strcpy(charholder,placeholder.c_str());
            strcpy(affiliation_array->affiliation[affiliation_array->number_of_affiliations].aff_name,charholder);
            delete charholder;

            affiliation_array->affiliation[affiliation_array->number_of_affiliations].type_value=pow(2,affiliation_array->number_of_affiliations);
            affiliation_array->number_of_affiliations++;
        }while( !(myfile.eof()) );
    }
    myfile.close();

    all_cards->number_of_characters=0;

    myfile.open("Data/characterNames.txt");

    if(myfile.is_open()){
        do{
            getline(myfile, placeholder, '\n');
            char *charholder = new char[placeholder.length()+1];
            strcpy(charholder,placeholder.c_str());
            strcpy(all_cards->card[all_cards->number_of_characters].name,charholder);
            delete charholder;
            all_cards->number_of_characters++;

        }while( !(myfile.eof()) );
    }

    myfile.close();

    myfile.open("Data/numericTypes.txt");

    if(myfile.is_open()){
        for(x=0;x<all_cards->number_of_characters;x++){
            is_not_same_aff=0;
            myfile >> all_cards->card[x].rarity >> all_cards->card[x].cost >> all_cards->card[x].number_of_types >> all_cards->card[x].affiliation_sum >> all_cards->card[x].is_awakened;
            all_cards->card[x].card_ID=x;
            if(x==0){
                unique_affiliations->card[0].rarity=all_cards->card[x].rarity;
                unique_affiliations->card[0].number_of_types=all_cards->card[x].number_of_types;
                unique_affiliations->card[0].affiliation_sum=all_cards->card[x].affiliation_sum;
                unique_affiliations->card[0].is_awakened=all_cards->card[x].is_awakened;
                unique_affiliations->card[0].card_ID=0;
                unique_affiliations->number_of_characters=1;
                unique_affiliations->card[0].cost=0;

            }else{
                for(y=0;y<x;y++){
                    if( (unique_affiliations->card[y].affiliation_sum!=all_cards->card[x].affiliation_sum) || (unique_affiliations->card[y].affiliation_sum==all_cards->card[x].affiliation_sum && unique_affiliations->card[y].rarity!=all_cards->card[x].rarity) ){
                        is_not_same_aff++;
                    }
                    if( (unique_affiliations->card[y].affiliation_sum==all_cards->card[x].affiliation_sum && unique_affiliations->card[y].rarity==all_cards->card[x].rarity && all_cards->card[x].is_awakened==1) ){
                        unique_affiliations->card[y].is_awakened=1;
                    }
                }

                if(is_not_same_aff==x){
                    unique_affiliations->card[unique_affiliations->number_of_characters].affiliation_sum=all_cards->card[x].affiliation_sum;
                    unique_affiliations->card[unique_affiliations->number_of_characters].rarity=all_cards->card[x].rarity;
                    unique_affiliations->card[unique_affiliations->number_of_characters].number_of_types=all_cards->card[x].number_of_types;
                    unique_affiliations->card[unique_affiliations->number_of_characters].is_awakened=all_cards->card[x].is_awakened;
                    unique_affiliations->card[unique_affiliations->number_of_characters].card_ID=unique_affiliations->number_of_characters;
                    unique_affiliations->card[unique_affiliations->number_of_characters].cost=0;
                    unique_affiliations->number_of_characters++;

                }
            }
        }
    }

    myfile.close();

    for(x=0;x<all_cards->number_of_characters;x++){
        all_cards->card[x].has_skill=false;
        all_cards->card[x].skill_ID=0;
        all_cards->card[x].skillcard_ID=0;
        strcpy(all_cards->card[x].skillname,"None");
    }

    for(x=0;x<allsupportskills->numberOfSkills;x++){
        for(y=0;y<allsupportskills->supportskill[x].numberOfCards;y++){
            for(z=0;z<all_cards->number_of_characters;z++){
                if(strcmp(allsupportskills->supportskill[x].supportskillcard[y].charactername,all_cards->card[z].name)==0 && allsupportskills->supportskill[x].supportskillcard[y].rarity==all_cards->card[z].rarity){
                    allsupportskills->supportskill[x].supportskillcard[y].card_ID=all_cards->card[z].card_ID;
                    all_cards->card[z].skill_ID=x;
                    all_cards->card[z].skillcard_ID=y;
                    strcpy(all_cards->card[z].skillname,allsupportskills->supportskill[x].skillName);
                    all_cards->card[z].has_skill=true;
                    allsupportskills->supportskill[x].supportskillcard[y].cost=all_cards->card[z].cost;
                }
            }
        }
    }

}


void create_affiliations(Affiliation_Array affiliation_array, ALL_Cards *all_cards){

    int upper_limit, i, j, k, m, n, p, q, r, place_sum, numTypes;
    double val1, val2, val3, val4, val5, val6;

    for(i=0;i<all_cards->number_of_characters;i++){
       place_sum=all_cards->card[i].affiliation_sum;
       numTypes=all_cards->card[i].number_of_types;

        for(j=0;j<affiliation_array.number_of_affiliations;j++){
            if(pow(2,j)>place_sum){
                upper_limit=j;
                break;
            }
        }
        if(j==affiliation_array.number_of_affiliations){
            upper_limit=affiliation_array.number_of_affiliations;
        }

        if(numTypes==1){
            for(j=0;j<upper_limit;j++)
                if(place_sum==pow(2,j)){
                    for(k=0;k<upper_limit;k++){
                        if(place_sum==affiliation_array.affiliation[k].type_value){
                            strcpy(all_cards->card[i].cardtype[0].affiliation,affiliation_array.affiliation[k].aff_name);
                        }
                    }
                break;
            }
        }else
            if(numTypes==2){
                for(j=0;j<upper_limit;j++){
                    for(k=0;k<upper_limit;k++){
                        if( (j!=k) && (pow(2,j)+pow(2,k)==place_sum) ){
                            val1=pow(2,j);
                            val2=pow(2,k);
                            for(m=0;m<upper_limit;m++){
                                if(val1==affiliation_array.affiliation[m].type_value){
                                    strcpy(all_cards->card[i].cardtype[0].affiliation,affiliation_array.affiliation[m].aff_name);
                                }
                                if(val2==affiliation_array.affiliation[m].type_value){
                                    strcpy(all_cards->card[i].cardtype[1].affiliation,affiliation_array.affiliation[m].aff_name);
                                }
                            }
                        }
                    }
                    if(strcmp(all_cards->card[i].cardtype[0].affiliation, "")!=0){
                        break;
                    }
                }
            }else
                if(numTypes==3){
                 for(j=0;j<upper_limit;j++){
                    for(k=0;k<upper_limit;k++){
                        for(m=0;m<upper_limit;m++){
                            if( (j!=k) && (k!=m) && (j!=m) && (pow(2,j)+pow(2,k)+pow(2,m)==place_sum) ){
                                val1=pow(2,j);
                                val2=pow(2,k);
                                val3=pow(2,m);
                                for(n=0;n<upper_limit;n++){
                                    if(val1==affiliation_array.affiliation[n].type_value){
                                        strcpy(all_cards->card[i].cardtype[0].affiliation,affiliation_array.affiliation[n].aff_name);
                                    }
                                    if(val2==affiliation_array.affiliation[n].type_value){
                                        strcpy(all_cards->card[i].cardtype[1].affiliation,affiliation_array.affiliation[n].aff_name);
                                    }
                                    if(val3==affiliation_array.affiliation[n].type_value){
                                        strcpy(all_cards->card[i].cardtype[2].affiliation,affiliation_array.affiliation[n].aff_name);
                                    }
                                }
                            }
                        }
                        if(strcmp(all_cards->card[i].cardtype[0].affiliation, "")!=0){
                            break;
                        }
                    }
                    if(strcmp(all_cards->card[i].cardtype[0].affiliation, "")!=0){
                        break;
                    }
                }
             }else
                if(numTypes==4){
                    for(j=0;j<upper_limit;j++){
                        for(k=0;k<upper_limit;k++){
                            for(m=0;m<upper_limit;m++){
                                for(n=0;n<upper_limit;n++){
                                    if( (j!=k) && (j!=m) && (j!=n) && (k!=m) && (k!=n) && (m!=n) && (pow(2,j)+pow(2,k)+pow(2,m)+pow(2,n)==place_sum)){
                                        val1=pow(2,j);
                                        val2=pow(2,k);
                                        val3=pow(2,m);
                                        val4=pow(2,n);
                                        for(p=0;p<upper_limit;p++){
                                            if(val1==affiliation_array.affiliation[p].type_value){
                                                strcpy(all_cards->card[i].cardtype[0].affiliation,affiliation_array.affiliation[p].aff_name);
                                            }
                                            if(val2==affiliation_array.affiliation[p].type_value){
                                                strcpy(all_cards->card[i].cardtype[1].affiliation,affiliation_array.affiliation[p].aff_name);
                                            }
                                            if(val3==affiliation_array.affiliation[p].type_value){
                                                strcpy(all_cards->card[i].cardtype[2].affiliation,affiliation_array.affiliation[p].aff_name);
                                            }
                                            if(val4==affiliation_array.affiliation[p].type_value){
                                                strcpy(all_cards->card[i].cardtype[3].affiliation,affiliation_array.affiliation[p].aff_name);
                                            }
                                        }
                                    }
                                }
                                if(strcmp(all_cards->card[i].cardtype[0].affiliation, "")!=0){
                                    break;
                                }
                            }
                            if(strcmp(all_cards->card[i].cardtype[0].affiliation, "")!=0){
                                break;
                            }
                        }
                        if(strcmp(all_cards->card[i].cardtype[0].affiliation, "")!=0){
                            break;
                        }
                    }
                }else
                    if(numTypes==5){
                        for(j=0;j<upper_limit;j++){
                            for(k=0;k<upper_limit;k++){
                                for(m=0;m<upper_limit;m++){
                                    for(n=0;n<upper_limit;n++){
                                        for(p=0;p<upper_limit;p++){
                                           if( (j!=k) && (j!=m) && (j!=n) && (j!=p) && (k!=m) && (k!=n) && (k!=p) && (m!=n) && (m!=p) && (n!=p) && (pow(2,j)+pow(2,k)+pow(2,m)+pow(2,n)+pow(2,p)==place_sum)){
                                                val1=pow(2,j);
                                                val2=pow(2,k);
                                                val3=pow(2,m);
                                                val4=pow(2,n);
                                                val5=pow(2,p);
                                                for(q=0;q<upper_limit;q++){
                                                    if(val1==affiliation_array.affiliation[q].type_value){
                                                        strcpy(all_cards->card[i].cardtype[0].affiliation,affiliation_array.affiliation[q].aff_name);
                                                    }
                                                    if(val2==affiliation_array.affiliation[q].type_value){
                                                        strcpy(all_cards->card[i].cardtype[1].affiliation,affiliation_array.affiliation[q].aff_name);
                                                    }
                                                    if(val3==affiliation_array.affiliation[q].type_value){
                                                        strcpy(all_cards->card[i].cardtype[2].affiliation,affiliation_array.affiliation[q].aff_name);
                                                    }
                                                    if(val4==affiliation_array.affiliation[q].type_value){
                                                        strcpy(all_cards->card[i].cardtype[3].affiliation,affiliation_array.affiliation[q].aff_name);
                                                        }
                                                    if(val5==affiliation_array.affiliation[q].type_value){
                                                        strcpy(all_cards->card[i].cardtype[4].affiliation,affiliation_array.affiliation[q].aff_name);
                                                    }
                                                }
                                            }
                                        }
                                        if(strcmp(all_cards->card[i].cardtype[0].affiliation, "")!=0){
                                            break;
                                        }
                                    }
                                    if(strcmp(all_cards->card[i].cardtype[0].affiliation, "")!=0){
                                        break;
                                    }
                                }
                                if(strcmp(all_cards->card[i].cardtype[0].affiliation, "")!=0){
                                    break;
                                }
                            }
                            if(strcmp(all_cards->card[i].cardtype[0].affiliation, "")!=0){
                                break;
                            }
                        }
                    }else
                        if(numTypes==6){
                                for(j=0;j<upper_limit;j++){
                                    for(k=0;k<upper_limit;k++){
                                        for(m=0;m<upper_limit;m++){
                                            for(n=0;n<upper_limit;n++){
                                                for(p=0;p<upper_limit;p++){
                                                    for(q=0;q<upper_limit;q++){
                                                        if( (j!=k) && (j!=m) && (j!=n) && (j!=p) && (j!=q) && (k!=m) && (k!=n) && (k!=p) && (k!=q) && (m!=n) && (m!=p) && (m!=q) && (n!=p) && (n!=q) && (p!=q) && (pow(2,j)+pow(2,k)+pow(2,m)+pow(2,n)+pow(2,p)+pow(2,q)==place_sum)){
                                                            val1=pow(2,j);
                                                            val2=pow(2,k);
                                                            val3=pow(2,m);
                                                            val4=pow(2,n);
                                                            val5=pow(2,p);
                                                            val6=pow(2,q);
                                                            for(r=0;r<upper_limit;r++){
                                                                if(val1==affiliation_array.affiliation[r].type_value){
                                                                    strcpy(all_cards->card[i].cardtype[0].affiliation,affiliation_array.affiliation[r].aff_name);
                                                                }
                                                                if(val2==affiliation_array.affiliation[r].type_value){
                                                                    strcpy(all_cards->card[i].cardtype[1].affiliation,affiliation_array.affiliation[r].aff_name);
                                                                }
                                                                if(val3==affiliation_array.affiliation[r].type_value){
                                                                    strcpy(all_cards->card[i].cardtype[2].affiliation,affiliation_array.affiliation[r].aff_name);
                                                                }
                                                                if(val4==affiliation_array.affiliation[r].type_value){
                                                                    strcpy(all_cards->card[i].cardtype[3].affiliation,affiliation_array.affiliation[r].aff_name);
                                                                    }
                                                                if(val5==affiliation_array.affiliation[r].type_value){
                                                                    strcpy(all_cards->card[i].cardtype[4].affiliation,affiliation_array.affiliation[r].aff_name);
                                                                }
                                                                if(val6==affiliation_array.affiliation[r].type_value){
                                                                    strcpy(all_cards->card[i].cardtype[5].affiliation,affiliation_array.affiliation[r].aff_name);
                                                                }
                                                            }
                                                        }
                                                    }
                                                    if(strcmp(all_cards->card[i].cardtype[0].affiliation, "")!=0){
                                                        break;
                                                    }
                                                }
                                                if(strcmp(all_cards->card[i].cardtype[0].affiliation, "")!=0){
                                                    break;
                                                }
                                            }
                                            if(strcmp(all_cards->card[i].cardtype[0].affiliation, "")!=0){
                                                break;
                                            }
                                        }
                                        if(strcmp(all_cards->card[i].cardtype[0].affiliation, "")!=0){
                                            break;
                                        }
                                    }
                                    if(strcmp(all_cards->card[i].cardtype[0].affiliation, "")!=0){
                                        break;
                                    }
                                }
                            }
    }
}


void reset_support_deck(SupportDeck *supportdeck){

    int i,j;

    supportdeck->number_of_skills=0;
    supportdeck->types_needed=0;
    supportdeck->numTypes_in_deck=0;
    supportdeck->bases_only=0;
    supportdeck->type_threshold=0;
    supportdeck->looking_for_specific_level=0;
    supportdeck->breaking_at_solution=0;
    supportdeck->breaking_early=0;

    supportdeck->solution_threshold_reached=false;

    for(i=0;i<SUPPORTDECK;i++){
        supportdeck->skill_locator[i]=0;
        supportdeck->card_locator[i]=0;
        supportdeck->skill_threshold[i]=0;
        supportdeck->num_allowed_cards[i]=0;
        supportdeck->num_ignored_cards[i]=0;
        strcpy(supportdeck->skills_in_deck[i],"");

        for(j=0;j<MAXSUPPORTCARDS;j++){
            supportdeck->ignore_list[i][j]=0;
        }
    }

    for(i=0;i<MAXTYPES;i++){
        strcpy(supportdeck->required_types[i].affiliation,"");
    }

    for(i=0;i<MAXAFFILIATIONS;i++){
        strcpy(supportdeck->current_types[i].aff_name,"");
        supportdeck->current_types[i].type_value=0.0;

        strcpy(supportdeck->current_base_types[i].aff_name,"");
        supportdeck->current_base_types[i].type_value=0.0;
    }

}


void set_min_max_costs(ALL_Cards *all_cards, ALL_Cards *unique_cards){

    int i,j, is_first=1;

    for(i=0;i<all_cards->number_of_characters;i++){
        all_cards->card[i].max_cost=0;
        all_cards->card[i].min_cost=0;
    }

    for(i=0;i<unique_cards->number_of_characters;i++){
        is_first=1;
        for(j=0;j<all_cards->number_of_characters;j++){
            if(all_cards->card[j].affiliation_sum==unique_cards->card[i].affiliation_sum && all_cards->card[j].rarity==unique_cards->card[i].rarity){
                if(is_first==1){
                    unique_cards->card[i].max_cost=all_cards->card[j].cost;
                    unique_cards->card[i].min_cost=all_cards->card[j].cost;
                    is_first=0;
                }

                if(all_cards->card[j].is_awakened==1){
                    if(ceil(1.1*all_cards->card[j].cost)>unique_cards->card[i].max_cost){
                        unique_cards->card[i].max_cost=ceil(1.1*all_cards->card[j].cost);
                    }

                    if(unique_cards->card[i].min_cost>ceil(1.1*all_cards->card[j].cost)){
                        unique_cards->card[i].min_cost=ceil(1.1*all_cards->card[j].cost);
                    }
                }
                if(all_cards->card[j].cost>unique_cards->card[i].max_cost){
                    unique_cards->card[i].max_cost=all_cards->card[j].cost;
                }

                if(unique_cards->card[i].min_cost>all_cards->card[j].cost){
                    unique_cards->card[i].min_cost=all_cards->card[j].cost;
                }

            }
        }
    }

}


double get_min_cost(ALL_Cards *all_cards, ALL_Cards *unique_cards, int support_array[SUPPORTDECK], int numSkills){

    int i;
    double cost=0.0;

    for(i=0;i<numSkills;i++){
        cost+=all_cards->card[support_array[i]].cost;
    }

    for(i=numSkills;i<SUPPORTDECK;i++){
        cost+=unique_cards->card[support_array[i]].min_cost;
    }

    return cost;
}


double get_max_cost(ALL_Cards *all_cards, ALL_Cards *unique_cards, int support_array[SUPPORTDECK], int numSkills){

    int i;
    double cost=0.0;

    for(i=0;i<numSkills;i++){
        cost+=all_cards->card[support_array[i]].cost;
    }

    for(i=numSkills;i<SUPPORTDECK;i++){
        cost+=unique_cards->card[support_array[i]].max_cost;
    }

    return cost;
}


double awaken_bonus(ALL_Cards *unique_cards, int index){

    if(unique_cards->card[index].is_awakened==0){
         return 0.0;
    }else{
        if(unique_cards->card[index].is_awakened==1){
            return 0.1;
        }else{
            return 0.0;
        }

    }
}


int generate_deck_types(SupportDeck *supportdeck, ALL_Cards *all_cards, ALL_Cards *unique_affiliations, int support_array[SUPPORTDECK]){

    int q, r, j;
    int aff_counter=0, current_type_counter=0;

    if(supportdeck->bases_only==1){
        //set first elements from support card 1
        for(q=0;q<all_cards->card[support_array[0]].number_of_types;q++){
            strcpy(supportdeck->current_types[q].aff_name,all_cards->card[support_array[0]].cardtype[q].affiliation);
            supportdeck->current_types[q].type_value+=all_cards->card[support_array[0]].rarity+(supportdeck->bases_only*(0.3+awaken_bonus(all_cards,support_array[0])));
            current_type_counter++;
        }

         //generate types in deck for rest of support cards
        for(j=1;j<supportdeck->number_of_skills;j++){
            for(q=0;q<all_cards->card[support_array[j]].number_of_types;q++){
                aff_counter=0;
                for(r=0;r<current_type_counter;r++){
                    if(strcmp(all_cards->card[support_array[j]].cardtype[q].affiliation,supportdeck->current_types[r].aff_name)==0){
                        supportdeck->current_types[r].type_value+=all_cards->card[support_array[j]].rarity+(supportdeck->bases_only*(0.3+awaken_bonus(all_cards,support_array[j])));
                    }else
                        if(strcmp(all_cards->card[support_array[j]].cardtype[q].affiliation,supportdeck->current_types[r].aff_name)!=0){
                            aff_counter++;
                        }

                } //closes r loop
                //creates a new type entry if cardtype[q] for card j doesn't match any current types
                if(aff_counter==current_type_counter){
                    strcpy(supportdeck->current_types[current_type_counter].aff_name,all_cards->card[support_array[j]].cardtype[q].affiliation);
                    supportdeck->current_types[current_type_counter].type_value+=all_cards->card[support_array[j]].rarity+(supportdeck->bases_only*(0.3+awaken_bonus(all_cards,support_array[j])));
                    current_type_counter++;
                }
            } //closes q loop for number of cardtypes belonging to card j
        } //closes j loop for checking and adding cardtype values

        // types for non-support skills
        for(j=supportdeck->number_of_skills;j<SUPPORTDECK;j++){
            for(q=0;q<unique_affiliations->card[support_array[j]].number_of_types;q++){
                aff_counter=0;
                for(r=0;r<current_type_counter;r++){
                    if(strcmp(unique_affiliations->card[support_array[j]].cardtype[q].affiliation,supportdeck->current_types[r].aff_name)==0){
                        supportdeck->current_types[r].type_value+=unique_affiliations->card[support_array[j]].rarity+(supportdeck->bases_only*(0.3+awaken_bonus(unique_affiliations,support_array[j])));
                    }else
                        if(strcmp(unique_affiliations->card[support_array[j]].cardtype[q].affiliation,supportdeck->current_types[r].aff_name)!=0){
                            aff_counter++;
                        }

                } //closes r loop
                //creates a new type entry if cardtype[q] for card j doesn't match any current types
                if(aff_counter==current_type_counter){
                    strcpy(supportdeck->current_types[current_type_counter].aff_name,unique_affiliations->card[support_array[j]].cardtype[q].affiliation);
                    supportdeck->current_types[current_type_counter].type_value+=unique_affiliations->card[support_array[j]].rarity+(supportdeck->bases_only*(0.3+awaken_bonus(unique_affiliations,support_array[j])));
                    current_type_counter++;
                }
            } //closes q loop for number of cardtypes belonging to card j
        } //closes j loop for checking and adding cardtype values

    }else
        if(supportdeck->bases_only==0){
            //set first elements from support card 1
            for(q=0;q<all_cards->card[support_array[0]].number_of_types;q++){
                strcpy(supportdeck->current_base_types[q].aff_name,all_cards->card[support_array[0]].cardtype[q].affiliation);
                supportdeck->current_base_types[q].type_value+=all_cards->card[support_array[0]].rarity+(supportdeck->bases_only*(0.3+awaken_bonus(all_cards,support_array[0])));
                current_type_counter++;
            }

             //generate types in deck for rest of support cards
            for(j=1;j<supportdeck->number_of_skills;j++){
                for(q=0;q<all_cards->card[support_array[j]].number_of_types;q++){
                    aff_counter=0;
                    for(r=0;r<current_type_counter;r++){
                        if(strcmp(all_cards->card[support_array[j]].cardtype[q].affiliation,supportdeck->current_base_types[r].aff_name)==0){
                            supportdeck->current_base_types[r].type_value+=all_cards->card[support_array[j]].rarity+(supportdeck->bases_only*(0.3+awaken_bonus(all_cards,support_array[j])));
                        }else
                            if(strcmp(all_cards->card[support_array[j]].cardtype[q].affiliation,supportdeck->current_base_types[r].aff_name)!=0){
                                aff_counter++;
                            }

                    } //closes r loop
                    //creates a new type entry if cardtype[q] for card j doesn't match any current types
                    if(aff_counter==current_type_counter){
                        strcpy(supportdeck->current_base_types[current_type_counter].aff_name,all_cards->card[support_array[j]].cardtype[q].affiliation);
                        supportdeck->current_base_types[current_type_counter].type_value+=all_cards->card[support_array[j]].rarity+(supportdeck->bases_only*(0.3+awaken_bonus(all_cards,support_array[j])));
                        current_type_counter++;
                    }
                } //closes q loop for number of cardtypes belonging to card j
            } //closes j loop for checking and adding cardtype values

            // types for non-support skills
            for(j=supportdeck->number_of_skills;j<SUPPORTDECK;j++){
                for(q=0;q<unique_affiliations->card[support_array[j]].number_of_types;q++){
                    aff_counter=0;
                    for(r=0;r<current_type_counter;r++){
                        if(strcmp(unique_affiliations->card[support_array[j]].cardtype[q].affiliation,supportdeck->current_base_types[r].aff_name)==0){
                            supportdeck->current_base_types[r].type_value+=unique_affiliations->card[support_array[j]].rarity+(supportdeck->bases_only*(0.3+awaken_bonus(unique_affiliations,support_array[j])));
                        }else
                            if(strcmp(unique_affiliations->card[support_array[j]].cardtype[q].affiliation,supportdeck->current_base_types[r].aff_name)!=0){
                                aff_counter++;
                            }

                    } //closes r loop
                    //creates a new type entry if cardtype[q] for card j doesn't match any current types
                    if(aff_counter==current_type_counter){
                        strcpy(supportdeck->current_base_types[current_type_counter].aff_name,unique_affiliations->card[support_array[j]].cardtype[q].affiliation);
                        supportdeck->current_base_types[current_type_counter].type_value+=unique_affiliations->card[support_array[j]].rarity+(supportdeck->bases_only*(0.3+awaken_bonus(unique_affiliations,support_array[j])));
                        current_type_counter++;
                    }
                } //closes q loop for number of cardtypes belonging to card j
            } //closes j loop for checking and adding cardtype values
        }

    return current_type_counter;
}


void print_output(SupportDeck *supportdeck, AllSupportSkills *allsupportskills, ALL_Cards *all_cards, ALL_Cards *unique_affiliations, int skill_level[SUPPORTDECK], int support_array[SUPPORTDECK], ofstream& output_file){

    int j, k, x, m;

    //skills
    for(j=0;j<supportdeck->number_of_skills;j++){
        output_file << "\t" << allsupportskills->supportskill[supportdeck->skill_locator[j]].skillName << ", level " << skill_level[j] << "\n";
    }

    output_file << "\n";

    //support cards
    for(j=0;j<supportdeck->number_of_skills;j++){
        output_file << all_cards->card[support_array[j]].rarity << "*  " << all_cards->card[support_array[j]].name;

        if(j+1<supportdeck->number_of_skills){
            output_file << "   ";
        }

    }

    output_file << "\n\n";

    //printing out support skill type requirements
    for(k=0;k<supportdeck->number_of_skills;k++){
        for(j=0;j<allsupportskills->supportskill[supportdeck->skill_locator[k]].numberOfCards;j++){
            if(strcmp(allsupportskills->supportskill[supportdeck->skill_locator[k]].supportskillcard[j].charactername,all_cards->card[support_array[k]].name)==0){
                output_file << allsupportskills->supportskill[supportdeck->skill_locator[k]].supportskillcard[j].supportskillreqs[skill_level[k]-1].typereq << " (";
                for(x=0;x<allsupportskills->supportskill[supportdeck->skill_locator[k]].supportskillcard[j].numTypeReq;x++){
                    output_file << allsupportskills->supportskill[supportdeck->skill_locator[k]].supportskillcard[j].types_needed[x].affiliation;

                    if(x+1<allsupportskills->supportskill[supportdeck->skill_locator[k]].supportskillcard[j].numTypeReq){
                        output_file << ",  ";
                    }
                }

                if(k+1<supportdeck->number_of_skills){
                    output_file << ")  ";
                }else{
                    output_file << ")";
                }

            }
        }
    }

    output_file << "\n\n";

    //non-support cards
    for(j=supportdeck->number_of_skills;j<SUPPORTDECK;j++){
        output_file << "\t" << unique_affiliations->card[support_array[j]].rarity << "*  ";
        for(m=0;m<unique_affiliations->card[support_array[j]].number_of_types;m++){
            output_file << unique_affiliations->card[support_array[j]].cardtype[m].affiliation;
            if(m+1<unique_affiliations->card[support_array[j]].number_of_types){
                output_file << ",  ";
            }
        }

        if(unique_affiliations->card[support_array[j]].is_awakened==1 && supportdeck->bases_only==1){
            output_file << "\t(calculated with awakened bonus)";
        }

        output_file << "\n";
    }

    output_file << "\n\n";

    if(supportdeck->bases_only==1){
    for(j=0;j<supportdeck->numTypes_in_deck;j++){
        output_file << supportdeck->current_types[j].type_value << " (" << supportdeck->current_types[j].aff_name;

        if(j+1<supportdeck->numTypes_in_deck){
            output_file << ")  ";
        }else{
            output_file << ")";
        }
    }
    }else
        if(supportdeck->bases_only==0){
            for(j=0;j<supportdeck->numTypes_in_deck;j++){
                output_file << supportdeck->current_base_types[j].type_value << " (" << supportdeck->current_base_types[j].aff_name;

                if(j+1<supportdeck->numTypes_in_deck){
                    output_file << ")  ";
                }else{
                    output_file << ")";
                }
            }
        }

    output_file << "\n\n";

    output_file << "Minimum cost: " << get_min_cost(all_cards, unique_affiliations, support_array, supportdeck->number_of_skills) << "\t\t\tMaximum Cost: " << get_max_cost(all_cards, unique_affiliations,support_array,supportdeck->number_of_skills);

    output_file << "\n\n";

    output_file << setfill('-') << setw(70) << "-" << "\n\n";

}


int skill_level_check(AllSupportSkills *allsupportskills, SupportDeck *supportdeck, int skill_card_locator[SUPPORTDECK], int skill_threshold[SUPPORTDECK]){

    int j, r, q, p, i, skill_match_counter=0, type1_match, type2_match, type3_match;

    for(i=0;i<supportdeck->number_of_skills;i++){
        skill_threshold[i]=0;
    }

    if(supportdeck->bases_only==1){
        for(j=0;j<supportdeck->number_of_skills;j++){
            if(allsupportskills->supportskill[supportdeck->skill_locator[j]].supportskillcard[skill_card_locator[j]].numTypeReq==1){
                for(r=0;r<supportdeck->numTypes_in_deck;r++){
                    if(strcmp(allsupportskills->supportskill[supportdeck->skill_locator[j]].supportskillcard[skill_card_locator[j]].types_needed[0].affiliation,supportdeck->current_types[r].aff_name)==0){
                            type1_match=r;

                            for(i=0;i<allsupportskills->supportskill[supportdeck->skill_locator[j]].max_level;i++){
                                if((allsupportskills->supportskill[supportdeck->skill_locator[j]].supportskillcard[skill_card_locator[j]].supportskillreqs[i].typereq<=supportdeck->current_types[type1_match].type_value) ){
                                    skill_threshold[j]++;
                                }
                        }
                    } //closes if strcmp for the two types
                } //closes r for loop
               }else
                if(allsupportskills->supportskill[supportdeck->skill_locator[j]].supportskillcard[skill_card_locator[j]].numTypeReq==2){
                    for(q=0;q<supportdeck->numTypes_in_deck;q++){
                        for(r=0;r<supportdeck->numTypes_in_deck;r++){
                            if( (strcmp(allsupportskills->supportskill[supportdeck->skill_locator[j]].supportskillcard[skill_card_locator[j]].types_needed[0].affiliation,supportdeck->current_types[q].aff_name)==0) && ((strcmp(allsupportskills->supportskill[supportdeck->skill_locator[j]].supportskillcard[skill_card_locator[j]].types_needed[1].affiliation,supportdeck->current_types[r].aff_name)==0)) ){
                                    type1_match=q;
                                    type2_match=r;

                                    for(i=0;i<allsupportskills->supportskill[supportdeck->skill_locator[j]].max_level;i++){
                                        if( (allsupportskills->supportskill[supportdeck->skill_locator[j]].supportskillcard[skill_card_locator[j]].supportskillreqs[i].typereq<=supportdeck->current_types[type1_match].type_value) && (allsupportskills->supportskill[supportdeck->skill_locator[j]].supportskillcard[skill_card_locator[j]].supportskillreqs[i].typereq<=supportdeck->current_types[type2_match].type_value) ){
                                            skill_threshold[j]++;
                                        }
                                    }

                            } //closes if strcmp for the two types
                        } //closes r for loop
                    } //closes q for loop
                    }else
                    if(allsupportskills->supportskill[supportdeck->skill_locator[j]].supportskillcard[skill_card_locator[j]].numTypeReq==3){
                        for(q=0;q<supportdeck->numTypes_in_deck;q++){
                            for(r=0;r<supportdeck->numTypes_in_deck;r++){
                                for(p=0;p<supportdeck->numTypes_in_deck;p++){
                                    if( (strcmp(allsupportskills->supportskill[supportdeck->skill_locator[j]].supportskillcard[skill_card_locator[j]].types_needed[0].affiliation,supportdeck->current_types[q].aff_name)==0) && ((strcmp(allsupportskills->supportskill[supportdeck->skill_locator[j]].supportskillcard[skill_card_locator[j]].types_needed[1].affiliation,supportdeck->current_types[r].aff_name)==0)) && ((strcmp(allsupportskills->supportskill[supportdeck->skill_locator[j]].supportskillcard[skill_card_locator[j]].types_needed[2].affiliation,supportdeck->current_types[p].aff_name)==0) )){
                                            type1_match=q;
                                            type2_match=r;
                                            type3_match=p;

                                            for(i=0;i<allsupportskills->supportskill[supportdeck->skill_locator[j]].max_level;i++){
                                                if( (allsupportskills->supportskill[supportdeck->skill_locator[j]].supportskillcard[skill_card_locator[j]].supportskillreqs[i].typereq<=supportdeck->current_types[type1_match].type_value) && (allsupportskills->supportskill[supportdeck->skill_locator[j]].supportskillcard[skill_card_locator[j]].supportskillreqs[i].typereq<=supportdeck->current_types[type2_match].type_value) && (allsupportskills->supportskill[supportdeck->skill_locator[j]].supportskillcard[skill_card_locator[j]].supportskillreqs[i].typereq<=supportdeck->current_types[type3_match].type_value) ){
                                                    skill_threshold[j]++;
                                                }
                                            }

                                    } //closes if strcmp for the three types
                            } //closes p for loop
                        } //closes r for loop
                    } //closes q for loop
            } //closes 3 type skill

            if(skill_threshold[j]!=0){
                skill_match_counter++;
            }

            if(skill_match_counter!=j+1){
                goto skill_level_fail;
            }
        } //closes j for loop, ending support level checker

    }else
        if(supportdeck->bases_only==0){
            for(j=0;j<supportdeck->number_of_skills;j++){
                if(allsupportskills->supportskill[supportdeck->skill_locator[j]].supportskillcard[skill_card_locator[j]].numTypeReq==1){
                    for(r=0;r<supportdeck->numTypes_in_deck;r++){
                        if(strcmp(allsupportskills->supportskill[supportdeck->skill_locator[j]].supportskillcard[skill_card_locator[j]].types_needed[0].affiliation,supportdeck->current_base_types[r].aff_name)==0){
                                type1_match=r;

                                for(i=0;i<allsupportskills->supportskill[supportdeck->skill_locator[j]].max_level;i++){
                                    if((allsupportskills->supportskill[supportdeck->skill_locator[j]].supportskillcard[skill_card_locator[j]].supportskillreqs[i].typereq<=supportdeck->current_base_types[type1_match].type_value) ){
                                        skill_threshold[j]++;
                                    }
                            }
                        } //closes if strcmp for the two types
                    } //closes r for loop
                   }else
                    if(allsupportskills->supportskill[supportdeck->skill_locator[j]].supportskillcard[skill_card_locator[j]].numTypeReq==2){
                        for(q=0;q<supportdeck->numTypes_in_deck;q++){
                            for(r=0;r<supportdeck->numTypes_in_deck;r++){
                                if( (strcmp(allsupportskills->supportskill[supportdeck->skill_locator[j]].supportskillcard[skill_card_locator[j]].types_needed[0].affiliation,supportdeck->current_base_types[q].aff_name)==0) && ((strcmp(allsupportskills->supportskill[supportdeck->skill_locator[j]].supportskillcard[skill_card_locator[j]].types_needed[1].affiliation,supportdeck->current_base_types[r].aff_name)==0)) ){
                                        type1_match=q;
                                        type2_match=r;

                                        for(i=0;i<allsupportskills->supportskill[supportdeck->skill_locator[j]].max_level;i++){
                                            if( (allsupportskills->supportskill[supportdeck->skill_locator[j]].supportskillcard[skill_card_locator[j]].supportskillreqs[i].typereq<=supportdeck->current_base_types[type1_match].type_value) && (allsupportskills->supportskill[supportdeck->skill_locator[j]].supportskillcard[skill_card_locator[j]].supportskillreqs[i].typereq<=supportdeck->current_base_types[type2_match].type_value) ){
                                                skill_threshold[j]++;
                                            }
                                        }

                                } //closes if strcmp for the two types
                            } //closes r for loop
                        } //closes q for loop
                        }else
                        if(allsupportskills->supportskill[supportdeck->skill_locator[j]].supportskillcard[skill_card_locator[j]].numTypeReq==3){
                            for(q=0;q<supportdeck->numTypes_in_deck;q++){
                                for(r=0;r<supportdeck->numTypes_in_deck;r++){
                                    for(p=0;p<supportdeck->numTypes_in_deck;p++){
                                        if( (strcmp(allsupportskills->supportskill[supportdeck->skill_locator[j]].supportskillcard[skill_card_locator[j]].types_needed[0].affiliation,supportdeck->current_base_types[q].aff_name)==0) && ((strcmp(allsupportskills->supportskill[supportdeck->skill_locator[j]].supportskillcard[skill_card_locator[j]].types_needed[1].affiliation,supportdeck->current_base_types[r].aff_name)==0)) && ((strcmp(allsupportskills->supportskill[supportdeck->skill_locator[j]].supportskillcard[skill_card_locator[j]].types_needed[2].affiliation,supportdeck->current_base_types[p].aff_name)==0) )){
                                                type1_match=q;
                                                type2_match=r;
                                                type3_match=p;

                                                for(i=0;i<allsupportskills->supportskill[supportdeck->skill_locator[j]].max_level;i++){
                                                    if( (allsupportskills->supportskill[supportdeck->skill_locator[j]].supportskillcard[skill_card_locator[j]].supportskillreqs[i].typereq<=supportdeck->current_base_types[type1_match].type_value) && (allsupportskills->supportskill[supportdeck->skill_locator[j]].supportskillcard[skill_card_locator[j]].supportskillreqs[i].typereq<=supportdeck->current_base_types[type2_match].type_value) && (allsupportskills->supportskill[supportdeck->skill_locator[j]].supportskillcard[skill_card_locator[j]].supportskillreqs[i].typereq<=supportdeck->current_base_types[type3_match].type_value) ){
                                                        skill_threshold[j]++;
                                                    }
                                                }

                                        } //closes if strcmp for the three types
                                } //closes p for loop
                            } //closes r for loop
                        } //closes q for loop
                } //closes 3 type skill

                if(skill_threshold[j]!=0){
                    skill_match_counter++;
                }

                if(skill_match_counter!=j+1){
                    goto skill_level_fail;
                }
            } //closes j for loop, ending support level checker
        }

    skill_level_fail:;

    return skill_match_counter;
}


int get_numTypes_needed(AllSupportSkills *allsupportskills, SupportDeck *supportdeck, int SKCD_locator[SUPPORTDECK]){

    int aff_counter=0, i, q, r, type_counter=0;

	//set first card's q required types
	for(q=0;q<allsupportskills->supportskill[supportdeck->skill_locator[0]].supportskillcard[SKCD_locator[0]].numTypeReq;q++){
		strcpy(supportdeck->required_types[q].affiliation,allsupportskills->supportskill[supportdeck->skill_locator[0]].supportskillcard[SKCD_locator[0]].types_needed[q].affiliation);
        type_counter++;
	}

	for(i=1;i<supportdeck->number_of_skills;i++){
		for(q=0;q<allsupportskills->supportskill[supportdeck->skill_locator[i]].supportskillcard[SKCD_locator[i]].numTypeReq;q++){
            aff_counter=0;

            for(r=0;r<type_counter;r++){
                if(strcmp(supportdeck->required_types[r].affiliation,allsupportskills->supportskill[supportdeck->skill_locator[i]].supportskillcard[SKCD_locator[i]].types_needed[q].affiliation)!=0){
                    aff_counter++;
                }
            }

            if(aff_counter==type_counter){
                strcpy(supportdeck->required_types[type_counter].affiliation,allsupportskills->supportskill[supportdeck->skill_locator[i]].supportskillcard[SKCD_locator[i]].types_needed[q].affiliation);
                type_counter++;
            }
        }
	}

    return type_counter;
}


int get_skill_match(ALL_Cards *all_cards, SupportDeck *supportdeck , int INDEX){

    int matches_type_req=0, p,r;

    for(p=0;p<all_cards->card[INDEX].number_of_types;p++){
        for(r=0;r<supportdeck->types_needed;r++){
            if(strcmp(all_cards->card[INDEX].cardtype[p].affiliation,supportdeck->required_types[r].affiliation)==0){
                matches_type_req++;
            }
        }
    }

    return matches_type_req;
}


int filter_unique_profiles(ALL_Cards *unique_profiles, SupportDeck *supportdeck, int unique_match_id[MAXCHARACTERS], int size_of_tracker){
    int i, type_match_counter=0, filter_entries=0;

    for(i=0;i<size_of_tracker;i++){
        type_match_counter=0;
        type_match_counter=get_skill_match(unique_profiles,supportdeck,i);

        if(type_match_counter>=supportdeck->type_threshold){
            unique_match_id[filter_entries]=i;
            filter_entries++;
        }
    }

    return filter_entries;

}


void print_locations(AllSupportSkills *allsupportskill, SupportDeck *supportdeck, int skl_cd_loc[SUPPORTDECK]){

    int i;

    cout << setfill('-') << setw(50) << "-" << "\n\n";

    for(i=0;i<supportdeck->number_of_skills;i++){
        cout << "checking skill card " << i+1 << ", " << skl_cd_loc[i]+1 << "/" << allsupportskill->supportskill[supportdeck->skill_locator[i]].numberOfCards;
        cout << ", " << allsupportskill->supportskill[supportdeck->skill_locator[i]].supportskillcard[skl_cd_loc[i]].charactername << "\n\n";
    }

    cout << setfill('-') << setw(50) << "-" << "\n\n";

}


void reset_types_in_deck(SupportDeck *supportdeck){
    int p;

    //erase previous run's values
    for(p=0;p<supportdeck->numTypes_in_deck;p++){
        supportdeck->current_types[p].type_value=0.0;
        strcpy(supportdeck->current_types[p].aff_name,"");

        supportdeck->current_base_types[p].type_value=0.0;
        strcpy(supportdeck->current_base_types[p].aff_name,"");
    }

    supportdeck->numTypes_in_deck=0;

}


void create_skillcard_entries(AllSupportSkills *allsupportskills, SupportDeck *supportdeck, int skill_card_locator[SUPPORTDECK]){

    int i;

    for(i=0;i<supportdeck->number_of_skills;i++){
        supportdeck->card_locator[i]=allsupportskills->supportskill[supportdeck->skill_locator[i]].supportskillcard[skill_card_locator[i]].card_ID;
    }
}


void print_endround_info(double run_start, double run_end, int entry_tracker[MAXSUPPORTCARDS], int index){

     //time to complete each i iteration
    if(difftime(run_end,run_start)>=3600){
        cout << "The time to complete this run was " << difftime(run_end,run_start)/3600 << " hours\n\n";
    }else
        if(difftime(run_end,run_start)>=60){
            cout << "The time to complete this run was " << difftime(run_end,run_start)/60 << " minutes\n\n";
        }else{
            cout << "The time to complete this run was " << difftime(run_end,run_start) << " seconds\n\n";
        }

    if(entry_tracker[index]>0){
        cout << entry_tracker[index] << " total combinations discovered\n";
        if(index>0){
            cout << "\t" << entry_tracker[index] - entry_tracker[index-1] << " new combinations found last run\n";
        }
    }else{
        cout <<  "\n\tNo combinations discovered!\n";
    }

    cout << "\n";

}


int skill_threshold_check(SupportDeck *supportdeck, int skill_level_tracker[SUPPORTDECK]){

    int i, threshold_check=0;

    for(i=0;i<supportdeck->number_of_skills;i++){
        if(skill_level_tracker[i]>=supportdeck->skill_threshold[i]){
            threshold_check++;
        }
    }

    return threshold_check;
}


void filter_allowed_skill_cards(SupportDeck *supportdeck, AllSupportSkills *allsupportskills, int skill_card_array[SUPPORTDECK][MAXSUPPORTCARDS]){

    int i,j,k, not_on_list, will_search;

    for(i=0;i<supportdeck->number_of_skills;i++){
        will_search=0;
        for(j=0;j<allsupportskills->supportskill[supportdeck->skill_locator[i]].numberOfCards;j++){
            not_on_list=0;
            for(k=0;k<supportdeck->num_ignored_cards[i];k++){
                if(supportdeck->ignore_list[i][k]!=allsupportskills->supportskill[supportdeck->skill_locator[i]].supportskillcard[j].skillcard_ID){
                    not_on_list++;
                }
            }

            if(not_on_list==supportdeck->num_ignored_cards[i]){
                skill_card_array[i][will_search]=allsupportskills->supportskill[supportdeck->skill_locator[i]].supportskillcard[j].skillcard_ID;
                will_search++;
            }
        }
    }

}


void presearch_config(AllSupportSkills *allsupportskills, ALL_Cards *unique_affiliations, SupportDeck *supportdeck, int skill_card_locator[SUPPORTDECK], int effective_chars, int unique_profile_match[MAXCHARACTERS], int &numChars){

    print_locations(allsupportskills, supportdeck, skill_card_locator);

    create_skillcard_entries(allsupportskills, supportdeck, skill_card_locator);

    //record number of types needed
    supportdeck->types_needed=get_numTypes_needed(allsupportskills, supportdeck, skill_card_locator);

    numChars=filter_unique_profiles(unique_affiliations, supportdeck, unique_profile_match, effective_chars);

}


void find_combinations(SupportDeck *supportdeck, ALL_Cards *all_cards, ALL_Cards *unique_affiliations, AllSupportSkills *allsupportskills, int support_array[SUPPORTDECK], int skill_card_locator[SUPPORTDECK], int &entry_counter, int &base_entry_counter, int entry_tracker[MAXSUPPORTCARDS], int index, ofstream &myoutput, ofstream &baseoutput){

    int skill_match_counter=0, threshold_tracker=0, skill_level_tracker[SUPPORTDECK], base_skill_level_tracker[SUPPORTDECK];

    supportdeck->bases_only=1;

    reset_types_in_deck(supportdeck);

    //prepraring to create array with current affiliations
    supportdeck->numTypes_in_deck=generate_deck_types(supportdeck, all_cards, unique_affiliations, support_array);

    //skill match counter used to record how many skill thresholds are reached
    skill_match_counter=skill_level_check(allsupportskills, supportdeck, skill_card_locator, skill_level_tracker);

    if(skill_match_counter==supportdeck->number_of_skills){
        threshold_tracker=skill_threshold_check(supportdeck,skill_level_tracker);

        if(threshold_tracker==supportdeck->number_of_skills){
            if(supportdeck->looking_for_specific_level==1){
                supportdeck->bases_only=0;

                //prepraring to create array with current affiliations for base cards
                supportdeck->numTypes_in_deck=generate_deck_types(supportdeck, all_cards, unique_affiliations, support_array);

                //skill match counter used to record how many skill thresholds are reached
                skill_match_counter=skill_level_check(allsupportskills, supportdeck, skill_card_locator, base_skill_level_tracker);

                threshold_tracker=skill_threshold_check(supportdeck,base_skill_level_tracker);

                if(threshold_tracker==supportdeck->number_of_skills){
                    base_entry_counter++;
                    print_output(supportdeck, allsupportskills, all_cards, unique_affiliations, skill_level_tracker, support_array, baseoutput);
                }else{
                    supportdeck->bases_only=1;
                    entry_counter++;
                    print_output(supportdeck, allsupportskills, all_cards, unique_affiliations, skill_level_tracker, support_array, myoutput);
                }
            }else{
                //notate that a combination has been found
                entry_counter++;
                print_output(supportdeck, allsupportskills, all_cards, unique_affiliations, skill_level_tracker, support_array, myoutput);
            }
        } //end skill threshold check
    } //end skill level check

    entry_tracker[index]=entry_counter+base_entry_counter;

    if(supportdeck->breaking_early==1){
        if(entry_tracker[index]>=supportdeck->breaking_at_solution){
            supportdeck->solution_threshold_reached=true;
        }
    }

}
