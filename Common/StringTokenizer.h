#ifndef Foundation_StringTokenizer_INCLUDED
#define Foundation_StringTokenizer_INCLUDED


#include "Platform.h"
#include "Exception.h"
#include <vector>
#include <cstddef>



class  StringTokenizer
	/// A simple tokenizer that splits a string into
	/// tokens, which are separated by separator characters.
	/// An iterator is used to iterate over all tokens.
{
public:
	enum Options
	{
		TOK_IGNORE_EMPTY = 1, /// ignore empty tokens
		TOK_TRIM         = 2  /// remove leading and trailing whitespace from tokens
	};

	typedef std::vector<std::string>::const_iterator Iterator;

	StringTokenizer(const std::string& str, const std::string& separators, int options = 0);
		/// Splits the given string into tokens. The tokens are expected to be
		/// separated by one of the separator characters given in separators.
		/// Additionally, options can be specified:
		///   * TOK_IGNORE_EMPTY: empty tokens are ignored
		///   * TOK_TRIM: trailing and leading whitespace is removed from tokens.
		/// An empty token at the end of str is always ignored. For example,
		/// a StringTokenizer with the following arguments:
		///     StringTokenizer(",ab,cd,", ",");
		/// will produce three tokens, "", "ab" and "cd".

	~StringTokenizer();
		/// Destroys the tokenizer.

	Iterator begin() const;
	Iterator end() const;

	const std::string& operator [] (std::size_t index) const;
		/// Returns the index'th token.
		/// Throws a RangeException if the index is out of range.

	std::size_t count() const;
		/// Returns the number of tokens.

private:
	StringTokenizer(const StringTokenizer&);
	StringTokenizer& operator = (const StringTokenizer&);

	std::vector<std::string> _tokens;
};


//
// inlines
//


inline StringTokenizer::Iterator StringTokenizer::begin() const
{
	return _tokens.begin();
}


inline StringTokenizer::Iterator StringTokenizer::end() const
{
	return _tokens.end();
}


inline const std::string& StringTokenizer::operator [] (std::size_t index) const
{
	if (index >= _tokens.size()) throw RangeException();
	return _tokens[index];
}


inline std::size_t StringTokenizer::count() const
{
	return _tokens.size();
}



#endif // Foundation_StringTokenizer_INCLUDED
