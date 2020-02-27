template <class T> int lastIndexOf(const T *pData,size_t extent,T target)
{
	size_t uRet = extent - 1;
	const T *pTest = pData + uRet;
	while (pTest >= pData) {
		if (*pTest-- == target) {
			return static_cast<int>(uRet);
		}
		--uRet;
	}
	return -1;
}