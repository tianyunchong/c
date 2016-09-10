/**
 * 正则表达式测试使用
 * http://blog.chinaunix.net/uid-479984-id-2114941.html
 */
#include <stdio.h>
#include <regex.h>
#include <stdlib.h>
int main() {
	regex_t reg;
	char errbuf[1024];
	char *bematch = "hhhericchd@gmail.com";
	char *pattern = "h{3,10}(.*)@.{5}.(.*)";
	int nm = 10, regRes;
	regmatch_t pmatch[nm];
	if (regcomp(&reg, pattern, REG_EXTENDED) < 0) {
		regerror(10, &reg, errbuf, sizeof(errbuf));
		printf("err:%s\n", errbuf);
	}
	regRes =  regexec(&reg, bematch, nm, pmatch, 0);

	return 1;
}