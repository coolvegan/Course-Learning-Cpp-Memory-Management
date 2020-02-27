int someFunction(struct data *pData)
{
	SomeObject *pObject = new SomeObject(pData);
 	int numDataFields = pObject->numDataObjects;

	if (!pObject) {
		return -1;
	}
	.
	.
	.
	// retVal gets set in here somewhere
	delete pObject;
	return retVal;
}


















int someFunction(struct data *pData)
{
	auto_ptr<SomeObject> pObject (new SomeObject(pData));
 	int numDataFields = 0,
        retVal = -1;

	if (pObject) {
		numDataFields = pObject->numDataObjects;
		.
		.
		// retVal gets set in here somewhere
	}
	return retVal;
}



















int someFunction(struct data *pData)
{
	auto_ptr<SomeObject> pObject (null);
 	int numDataFields = 0,
        retVal = -1;

	try {
		pObject = new SomeObject(pData);
	}
	catch (std::bad_alloc & ba) {
		return retval;
	}

	numDataFields = pObject->numDataObjects;
	.
	.
	// retVal gets set in here somewhere
	return retVal;
}
