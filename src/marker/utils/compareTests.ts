import { BunFile } from "bun";

function notEqualUint8(a: Uint8Array, b: Uint8Array) {
    if (a.length === b.length) {
        let i = 0, len = a.length;
        while (i < len) {
            if (a[i] !== b[i])
                return true;
            ++i;
        }

        return false;
    }

    return true;
}

export default async function compareTests(source: BunFile, generated: BunFile) {
    const srcReader = source.stream().getReader(),
        genReader = generated.stream().getReader();

    let src: ReadableStreamDefaultReadResult<Uint8Array>,
        gen: ReadableStreamDefaultReadResult<Uint8Array>;

    while (true) {
        src = await srcReader.read();
        gen = await genReader.read();

        if (src.done !== gen.done)
            return false;
        if (src.done)
            return true;

        if (notEqualUint8(src.value, gen.value as Uint8Array))
            return false;
    }
}