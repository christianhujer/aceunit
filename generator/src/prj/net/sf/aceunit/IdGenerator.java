package net.sf.aceunit;

/**
 * Generator for consecutive Ids.
 *
 * @author <a href="mailto:cher@riedquat.de">Christian Hujer</a>
 */
public class IdGenerator {

    /**
     * The last used id.
     */
    private int lastId;

    /**
     * Creates an IdGenerator.
     * The {@link #lastId} will be 0 which means the id returned by {@link #getNextId()} will be 1.
     */
    public IdGenerator() {
        this(0);
    }

    /**
     * Creates an IdGenerator.
     *
     * @param lastId Last id used, the first call to {@link #getNextId()} will return that value + 1.
     */
    public IdGenerator(final int lastId) {
        this.lastId = lastId;
    }

    /**
     * Returns the next id.
     *
     * @return The next id.
     */
    public synchronized int getNextId() {
        return ++lastId;
    }

}
