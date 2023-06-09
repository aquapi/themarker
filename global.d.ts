declare module 'bun' {
    interface Env {
        KEY: Buffer;
        IV: Buffer
    }
}