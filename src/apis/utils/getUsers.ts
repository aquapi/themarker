const path = './src/apis/data/users.json';

export default async function getUsers() {
    return JSON.parse(await Bun.file(path).text()) as Record<string, {
        password: string, points: number[]
    }>;
}