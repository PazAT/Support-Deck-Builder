/**
    Here are the structures and function prototypes used for the entire program.
**/

struct CardType{

    string affiliation;

};
extern CardType cardtype;

struct Card{

    int number_of_types, rarity, evo_level, is_awakened, card_ID, skill_ID, skillcard_ID;
    int num_profiles_exact, num_profiles_awakened_exact, num_profiles_at_least, num_profiles_awakened_at_least;
    unsigned int affiliation_sum;
    double cost, min_cost, max_cost;
    string name, skillname;
    bool has_skill;
    CardType cardtype[MAXTYPES];

};
extern Card card;

struct ALL_Cards{

    Card card[MAXCHARACTERS];
    int number_of_characters;
};
extern ALL_Cards all_cards;
extern ALL_Cards unique_affiliations;

struct SupportSkillReqs{

    int level;
    double typereq;

};
extern SupportSkillReqs supportskillreqs;

struct SupportSkillCard{

    CardType types_needed[MAXAFFILIATIONS];
    string charactername;
    int current_level, numTypeReq, skillcard_ID, card_ID;
    double rarity, cost;
    SupportSkillReqs supportskillreqs[MAXSUPPORTLEVEL];

};
extern SupportSkillCard supportskillcard;

struct SupportSkill{

    string skillName, skillNickname;
    int max_level, numberOfCards, skill_ID;
    SupportSkillCard supportskillcard[MAXSUPPORTCARDS];

};
extern SupportSkill supportskill;

struct AllSupportSkills{

    SupportSkill supportskill[MAXSUPPORT];
    int numberOfSkills;

};
extern AllSupportSkills allsupportskills;

struct Affiliation{

    string aff_name;
    double type_value;

};
extern Affiliation affiliation;

struct Affiliation_Array{

    Affiliation affiliation[MAXAFFILIATIONS];
    int number_of_affiliations;
};
extern Affiliation_Array affiliation_array;
extern Affiliation_Array aff_counter;

struct SupportDeck{

    CardType required_types[MAXTYPES];
    Affiliation current_types[MAXAFFILIATIONS], current_base_types[MAXAFFILIATIONS];
    string skills_in_deck[SUPPORTDECK];
    int skill_locator[SUPPORTDECK], card_locator[SUPPORTDECK], skill_threshold[SUPPORTDECK];
    int number_of_skills, types_needed, numTypes_in_deck, bases_only, type_threshold;
    int looking_for_specific_level, ignore_list[SUPPORTDECK][MAXSUPPORTCARDS], breaking_early, breaking_at_solution;
    int num_allowed_cards[SUPPORTDECK], num_ignored_cards[SUPPORTDECK];
    bool solution_threshold_reached;

};
extern SupportDeck supportdeck;

void create_Database(AllSupportSkills* allsupportskills, ALL_Cards* all_cards, ALL_Cards* unique_affiliations, Affiliation_Array* affiliation_array);
void create_affiliations(Affiliation_Array *affiliation_array, ALL_Cards *all_cards);
void reset_support_deck(SupportDeck *supportdeck);
void set_min_max_costs(ALL_Cards *all_cards, ALL_Cards *unique_cards);
void print_info(AllSupportSkills *allsupportskills, ALL_Cards *all_cards);

void construct_support_deck(SupportDeck *supportdeck, AllSupportSkills *allsupportskills, ALL_Cards *all_cards, ALL_Cards *unique_affiliations, int effective_chars);
void print_output(SupportDeck *supportdeck, AllSupportSkills *allsupportskills, ALL_Cards *all_cards, ALL_Cards *unique_affiliations, int skill_level[SUPPORTDECK], int support_array[SUPPORTDECK], ofstream& output_file);
int generate_deck_types(SupportDeck *supportdeck, ALL_Cards *all_cards, ALL_Cards *unique_affiliations, int support_array[SUPPORTDECK]);
int skill_level_check(AllSupportSkills *allsupportskills, SupportDeck *supportdeck, int skill_card_locator[SUPPORTDECK], int skill_threshold[SUPPORTDECK]);
int get_numTypes_needed(AllSupportSkills *allsupportskills, SupportDeck *supportdeck, int SKCD_locator[SUPPORTDECK]);

int get_skill_match(ALL_Cards *all_cards, SupportDeck *supportdeck , int INDEX);
double awaken_bonus(ALL_Cards *unique_cards, int index);
void update_card_profiles(ALL_Cards all_card, ALL_Cards unique_afilliations, int size_of_tracker);
int filter_unique_profiles(ALL_Cards *unique_profiles, SupportDeck *supportdeck, int unique_match_id[MAXCHARACTERS], int size_of_tracker);
void print_locations(AllSupportSkills *allsupportskill, SupportDeck *supportdeck, int skl_cd_loc[SUPPORTDECK]);

void reset_types_in_deck(SupportDeck *supportdeck);
void create_skillcard_entries(AllSupportSkills *allsupportskills, SupportDeck *supportdeck, int skill_card_locator[SUPPORTDECK]);
void print_endround_info(double run_start, double run_end, int entry_tracker[SUPPORTDECK], int index);
int skill_threshold_check(SupportDeck *supportdeck, int skill_level_tracker[SUPPORTDECK]);
void filter_allowed_skill_cards(SupportDeck *supportdeck, AllSupportSkills *allsupportskills, int skill_card_array[SUPPORTDECK][MAXSUPPORTCARDS]);

double get_min_cost(ALL_Cards *all_cards, ALL_Cards *unique_cards, int support_array[SUPPORTDECK], int numSkills);
double get_max_cost(ALL_Cards *all_cards, ALL_Cards *unique_cards, int support_array[SUPPORTDECK], int numSkills);
void presearch_config(AllSupportSkills *allsupportskills, ALL_Cards *unique_affiliations, SupportDeck *supportdeck, int skill_card_locator[SUPPORTDECK], int effective_chars, int unique_profile_match[MAXCHARACTERS], int &numChars);
void find_combinations(SupportDeck *supportdeck, ALL_Cards *all_cards, ALL_Cards *unique_affiliations, AllSupportSkills *allsupportskills, int support_array[SUPPORTDECK], int skill_card_locator[SUPPORTDECK], int &entry_counter, int &base_entry_counter, int entry_tracker[MAXSUPPORTCARDS], int index, ofstream &myoutput, ofstream &baseoutput);


void count_affiliations(ALL_Cards *all_cards, ALL_Cards *unique_affiliations, Affiliation_Array *aff_counter);
void number_of_profiles(ALL_Cards *all_cards, ALL_Cards *unique_profiles);
void return_affiliation_numbers(ALL_Cards *all_cards, ALL_Cards *unique_profiles, int number);
void print_rarity(ALL_Cards *all_cards, ALL_Cards *unique_affiliations);
void count_affiliation_spread(ALL_Cards *all_cards, ALL_Cards *unique_affiliations);

void print_skills(AllSupportSkills allsupportskills);
void track_awaken(ALL_Cards *all_cards, ALL_Cards *unique_affiliations);
void print_exact_profiles(ALL_Cards *all_cards);
void check_stats(ALL_Cards *all_cards, ALL_Cards *unique_cards, Affiliation_Array *affiliation_array, AllSupportSkills *allsupportskills);
