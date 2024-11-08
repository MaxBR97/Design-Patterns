
abstract class Handler implements Chain_Of_Responsibility{
    protected Handler nextHandler;

    public Handler(){}
    
    public <T extends Handler> Handler(T h){
        nextHandler = h;
    }

    public void setNext(Handler h){
        nextHandler = h;
    }

    abstract public <T> void process(T request);

    public <T> void propagate(T request) {
        process(request);
        if(nextHandler!=null)
            nextHandler.propagate(request);
    }
}