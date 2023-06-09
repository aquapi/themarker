import { html, createForm, Event } from '@stricjs/arrow/utils';
import { daisyUI } from './utils/head';
import Background from './utils/background';

export function render() {
    if (sessionStorage.getItem('token'))
        return location.href = '/';

    const form = createForm<{ name: string, pass: string }>({ name: '', pass: '' });

    async function submit(e: Event<HTMLFormElement>) {
        e.preventDefault();
        const { name, pass } = form.data;

        try {
            const res = await fetch('/api/v1/login', {
                method: 'POST',
                body: JSON.stringify({ name, pass })
            });
            if (!res.ok) throw null;

            // Save token and move to next page
            sessionStorage.setItem('token', await res.text());
            alert('Log in successfully, press OK to continue...');
            location.href = '/';
        } catch (e) {
            alert('Invalid username or password');
        }
    }

    html`
        ${new Background('transparent', 1).template}
        <form class='card w-[20rem] bg-stone-50 shadow-inner form-control justify-center align-center text-gray-600'>
            <div class='card-body space-y-3'>
                <h3 class='card-title justify-center text-[18px]'>Hi there!</h3>
                <hr />

                <div class='space-y-2 flex-column'>
                    <input type='text' placeholder='Username...' 
                        class='input input-bordered input-md w-full max-w-xs' 
                        @input='${form.input('name')}'
                    />
                    <input type='password' placeholder='Password...' autocomplete
                        class='input input-bordered input-md w-full max-w-xs' 
                        @input='${form.input('pass')}'
                    />
                </div>

                <div class='card-actions'>
                    <a class="btn btn-wide btn-active btn-outline btn-sm normal-case text-[14px]" @click='${submit}'>Let me in</a>
                </div>
            </div>
        </form>
    `;
}

export const path = '/login';
export const head = daisyUI;