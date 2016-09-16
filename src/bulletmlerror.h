#ifndef BULLETMLERROR_H_
#define BULLETMLERROR_H_

#include "bulletmlcommon.h"

#include <stdexcept>

/// さすがにもうちょっと充実させんとねえ
class BULLETML_API BulletMLError : public std::runtime_error {
public:
	BulletMLError(const std::string& msg)
		: std::runtime_error(msg) {}

	static void doAssert(const char* str) {
		throw BulletMLError(str);
	}
	static void doAssert(const std::string& str) {
		throw BulletMLError(str);
	}
	static void doAssert(bool t, const char* str) {
		if (!t) throw BulletMLError(str);
	}
	static void doAssert(bool t, const std::string& str) {
		if (!t) throw BulletMLError(str);
	}

};

#endif // ! BULLETMLERROR_H_
