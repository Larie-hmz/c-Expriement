#include "shopcard.h"

Shopcard::Shopcard(Goods* & good_, const int & buyNumber_) {
	goodsCard = good_;
	buyNumber = buyNumber_;
}

Shopcard::Shopcard(const Shopcard& shop_) {
	goodsCard = shop_.goodsCard;
	buyNumber = shop_.buyNumber;
}
Shopcard::~Shopcard() {
	
}