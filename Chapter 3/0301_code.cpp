// sandwich pattern

// C

char *pBuffer = malloc(32000);
if (pBuffer) {
	doSomethingWith(pBuffer);
	free(pBuffer);
}

// C++

char *pBuffer = new (nothrow) char[32000];
if (pBuffer) {
	doSomethingWith(pBuffer);
}
delete [] pBuffer;

// ------------------------------------------------------

// virtual destructor chain

class c03_code
{
public:
	c03_code(arguments);
	virtual ~c03_code();

	/* data */
};

class c04_code : public c03_code
{
public:
	c04_code(arguments) : c03_code() {}
	virtual ~c04_code();

	/* data */
};

class c05_code
{
public:
	c05_code(arguments) : c04_code() {}
	virtual ~05_code();

	/* data */
};

// ------------------------------------------------------

// Reference versus value passing

bool propertyHasValue(Property p, Value v)
{
	return p.hasValue(v);
}

bool propertyHasValue(Property *p, Value *v)
{
	return (p) ? p->hasValue(v) : false;
}

bool propertyHasValue(const Property &p, const Value &v) // Unless const isn't an issue
{
	return p.hasvalue(v);
}

// ------------------------------------------------------

Factory method lifetime management

Object *pObj = ObjectFactory.getInstance(criterion);

Either you manage the lifetime:

delete pObj;

or the factory can do it for you:

ObjectFactory.returnInstance(pObj);

or perhaps it was better done this way:

auto_ptr<Object *>pObj(ObjectFactory.getInstance(criterion));

// ------------------------------------------------------

class BufferWrap {
public:
	BufferWrap (Buffer *pb) : m_pb(pb), m_pText(0)
	{}

	~BufferWrap () {
		if (m_pText) {
			free(m_pText);
		}
	}

	char *getString()
	{
		return (m_pText) ? m_pText : (m_pText = pb->getStringBuffer());
	}

private:
	Buffer *m_pb;
	char *m_pText;
};

Buffer buffr;
BufferWrap wrap(&buffr);

buffr << some_stuff;
buffr << some_more_stuff;

text_handler(wrap.getString());

// and done.

// Make sure that you use the correct delete with an object

class X {
public:
	X(int x) : m_x(x) {}
	X() : m_x(0) {}
	~X();
private:
	int m_x;
};

int _tmain(int argc, _TCHAR* argv[])
{
	X *pX = new X[34];

	delete [] pX;

	return 0;
}































