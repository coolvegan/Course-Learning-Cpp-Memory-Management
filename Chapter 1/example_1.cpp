MyClass myInstance = new myClass();  //C#

MyClass *myInstance = new MyClass(); //C++


void MyMethod(SomeResrouceType resource)
{
    MyClass myInstance = new MyClass(resource);
}

void MyMethod(SomeResourceType resource)
{
    MyClass *myInstance = new MyClass(resource);
}

void MyMethod(SomeResourceType resource)
{
    MyClass *myInstance = new MyClass(resource);
    .
    .
    .
    delete myInstance;
}

void MyMethod(SomeResourceType resource)
{
    MyClass myInstance(resource);
    // No need to clean up
}






