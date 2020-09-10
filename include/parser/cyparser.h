#ifdef EXTENDED_FEATURE
#include "parser.h"
#include "cydigest.h"
#include "cyl.h"

class CyParser: public Parser<CyDigest*> {
    public:
    CyDigest* parse(std::string file) override;
    void setLangBlock(LangBlock l) { lang_blk = l; }

    private:
    LangBlock lang_blk;
};
#endif
