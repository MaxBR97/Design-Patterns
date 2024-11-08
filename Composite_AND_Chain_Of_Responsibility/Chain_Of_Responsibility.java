
interface Chain_Of_Responsibility {
    public <T> void propagate(T obj);
}