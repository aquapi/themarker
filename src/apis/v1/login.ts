import { Handler } from '@stricjs/router';
import { encrypt } from '../utils/crypt';
import getUsers from '../utils/getUsers';

type LoginData = { pass: string, name: string };

const login: Handler<'/login'> = async req => {
    try {
        const users = await getUsers();
        const { name, pass }: LoginData = await req.json();

        if (name in users && pass === users[name].password)
            return new Response(encrypt(name));

        return new Response(null, { status: 403 });
    } catch (e) {
        return new Response(null, { status: 404 });
    }
};

export default login;