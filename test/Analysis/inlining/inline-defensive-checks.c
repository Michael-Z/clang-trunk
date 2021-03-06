// RUN: %clang_cc1 -analyze -analyzer-checker=core -verify %s

// Perform inline defensive checks.
void idc(int *p) {
	if (p)
		;
}

int test01(int *p) {
  if (p)
    ;
  return *p; // expected-warning {{Dereference of null pointer}}
}

int test02(int *p, int *x) {
  if (p)
    ;
  idc(p);
	if (x)
		;
  return *p; // expected-warning {{Dereference of null pointer}}
}

int test03(int *p, int *x) {
	idc(p);
	if (p)
		;
	return *p; // False negative
}

int deref04(int *p) {
  return *p; // expected-warning {{Dereference of null pointer}}
}

int test04(int *p) {
  if (p)
    ;
  idc(p);
  return deref04(p);
}

int test11(int *q, int *x) {
	int *p = q;
	if (q)
		;
	if (x)
		;
	return *p; // expected-warning{{Dereference of null pointer}}
}

int test12(int *q) {
	int *p = q;
	idc(q);
	return *p;
}

int test13(int *q) {
	int *p = q;
	idc(p);
	return *p;
}

int test21(int *q, int *x) {
	if (q)
		;
	if (x)
		;
	int *p = q;
	return *p; // expected-warning{{Dereference of null pointer}}
}

int test22(int *q, int *x) {
  idc(q);
	if (x)
		;
	int *p = q;
	return *p;
}

int test23(int *q, int *x) {
  idc(q);
	if (x)
		;
	int *p = q;
  if (!p)
    ;
	return *p; // False negative
}

void use(char *p) {
  if (!p)
    return;
  p[0] = 'a';
}

void test24(char *buffer) {
  use(buffer);
  buffer[1] = 'b';
}
