import { PageRouter, ignoreExts } from '@stricjs/arrow';
import router from './src/apis';
import { randomBytes } from 'crypto';

Bun.plugin(ignoreExts('jpg'));

// Set key and iv
process.env.KEY = randomBytes(32);
process.env.IV = randomBytes(12);

// Serve the page
new PageRouter({ 
    loader: {
        '.jpg': 'file'
    } 
})
    .set('root', import.meta.dir + '/src')
    .set('src', 'pages')
    .set('router', router)
    .serve();