
class Executor extends Handler {

    public Executor() {}

    public <T extends Handler> Executor( T handler){
        this.nextHandler = handler;
    }

    public <T> void process(T request) {
        if(request instanceof String){
            System.out.println("Executing");
        }
    }
}