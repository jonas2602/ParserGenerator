#include "Token.h"
#include "../ParserTypes.h"


namespace ParserCore {

	Token* Token::EOS_TOKEN = new Token(EOS_S, EOS, -1, -1, -1, -1);

}