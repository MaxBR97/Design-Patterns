
class Request <T> {
    private T value;
    public T get(){
        return value;
    }
    public void set(T val) {
        value = val;
    }
}