// 0101.cpp

//-- Not good.  It's wrong.

char BufferClass::getLastChar()
{
	return *(this->m_buffer + strlen(this->m_buffer));
}

//-- Better, but still not good: it's not wrong, but it's not right.

char BufferClass::getLastChar()
{
	return *(this->m_buffer + strlen(this->m_buffer) - 1);
}

//------------------------------

// It leaks

int Portfolio::finalTally(Asset &asset)
{
	AssetCalculator *pCalc = new AssetCalculator(asset);
	return pCalc->finalTally();
}

// Now you see it--now you don't.

char *Editor::extractClip(size_t startOffset, size_t endOffset)
{
	char szclip[MAX_BUFFER_SIZE] = {0};
	strcpy(szClip,GetClipSection(startOffset,endOffset));
	return szClip;
}

//------------------------------

void SomeClass:method()
{
	Asset *pAsset = new Asset();

	if (externalCondition()) {
		.
		.
		.
		.
		if (ruhRoh()) {
			delete pAsset;
		}
	} else {
		.
		.
		.
	}

	int iResult = pAsset->getValue();

	delete pAsset;

	return iResult;
}

//------------------------------

// In a debug build items get initialized; in release builds, they don't.

//------------------------------

int i;

for(i = 0; i < iMax; ++i) {
	if (exitCondition(i)) {
		break;
	}
}

printf("Found item at reference #%d\n",i);

