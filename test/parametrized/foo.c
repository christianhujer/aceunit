#define A_Test
#define A_With(X)

#define pname2(l) params ## l
#define pname(l) pname2(l)
#define debraceWithParams(type, ...) type pname(__LINE__)[] = __VA_ARGS__;
#define A_WithParams(X) debraceWithParams X

A_WithParams((int, { 5, 10 }))
void foo(int *p)
{

}

int paramsForBar[] = { 5, 10 };
A_Test
A_With(paramsForBar)
void bar(int *p)
{
}

int main(void)
{
}
