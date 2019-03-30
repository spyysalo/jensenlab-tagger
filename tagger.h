#ifndef __REFLECT_TAGGER_HEADER__
#define __REFLECT_TAGGER_HEADER__

#include <list>
#include <vector>
#include <unordered_set>
#include <boost/regex.hpp>

#include "tagger_types.h"

using namespace std;

class GetMatchesParams
{
	public:
		vector<int> entity_types;
		bool auto_detect;
		bool allow_overlap;
		bool find_acronyms;
		bool protect_tags;
		bool tokenize_characters;
		int  max_tokens;
		
	public:
		GetMatchesParams();
		GetMatchesParams(const char*);
		
	public:
		void add_entity_type(int entity_type);
        void load_entity_types(const char* types_filename);
};

class Tagger
{
	public:
		bool      serials_only;
		ORGANISMS organisms;
		
	protected:
		DICTIONARY    names;
		NAME_BOOL     global;
		DOC_NAME_BOOL local;
		
	protected:
		boost::regex re_stop;
		boost::regex re_html;
		boost::regex re_reflect;
		
	public:
		Tagger(bool serials_only, const char* pattern = NULL);
		~Tagger();
		
	public:
		void add_name(const char* name, int type, const char* identifier);
		void add_name(const char* name, int type, int serial);
		void allow_block_name(const char* name, const char* document_id, bool block);
		bool check_name(const char* name, int type, const char* identifier);
		bool is_blocked(const char* document_id, const char* name);
		Entities resolve_name(const char* name);
		
	public:
		void load_global(const char* global_filename);
		void load_local(const char* local_filename);
		void load_names(const char* entities_filename, const char* names_filename);
		void load_names(int type, const char* names_filename);
		
	public:
		Matches get_matches(char* document, char* document_id, const GetMatchesParams& params);
		
	private:
		void find_matches(Matches& matches, Acronyms& acronyms, Tokens& tokens, char* document, const char* document_id, const GetMatchesParams& params, const unordered_set<int>& entity_types);
		void trim_boundaries(const char* text, int& start, int& stop);
			
};

// This function is used by autogenerated SWIG code to allow fast shutdown.
void quit();

#include "tagger_core.h"

#endif
