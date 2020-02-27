
void MyMethod(SomeResourceType resource)
{
    MyClass *myInstance = new MyClass(resource);
    .
    .
    .
    delete myInstance;
}

void MyMethod(SomeResourceType &resource)
{
    auto_ptr<MyClass> my Instance (new MyInstance(resource));
    .
    .
    .
}

void MyMethod(SomeResourceType resource)
{
    MyClass myInstance(resource);
    // No need to clean up
}






