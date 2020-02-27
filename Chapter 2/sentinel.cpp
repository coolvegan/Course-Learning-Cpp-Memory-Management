
static const unsigned int OVERSIZE = 16UL;

struct MemHeader {
	size_t size;
	unsigned char aSentinel[OVERSIZE];
};

char *buffer_allocate(size_t size)
{
#if defined(_DEBUG)	
	char *ptrCh = NULL;
	if (size) {
		struct MemHeader header;
		size_t uBlockSize = size + sizeof(header) + OVERSIZE;
		header.size = size;
		memset(header.aSentinel,0xCF,sizeof(header.aSentinel));

		try {
			ptrCh = new char[uBlockSize];
			memset(ptrCh,0,uBlockSize);
			memcpy(ptrCh,&header,sizeof(header));
			memset(ptrCh + size + sizeof(header), 0xCF, OVERSIZE);
			ptrCh += sizeof(header);
		}
		catch (std::bad_alloc & ba) { // Choosing not to throw here
			ptrCh = NULL;
		} 
	}
	return ptrCh;
#else
	return new char[size];
#endif	
}


#if defined(_DEBUG)
bool buffer_boundsFail(char *pBuffer)
{
	
}
#else
#define buffer_boundsFail(a) ; // No code in release run-time
#endif

void buffer_deallocate(char *pBuffer)
{
#if defined(_DEBUG)	
	pBuffer -= sizeof(struct MemHeader);
#endif	
	delete [] pBuffer;
}