import { Component, template } from "@stricjs/arrow/utils";

const inlineStyles = `
    position:absolute;
    width:100vw;
    height:100vh
`; 

export default class Background extends Component {
    constructor(public color: string, public opacity: number = 0) {
        super();
    } 

    get template() {
        return template`
            <div style='
                background: rgb(57,51,51);
                background: linear-gradient(90deg, rgba(57,51,51,1) 14%, rgba(180,174,185,1) 50%, rgba(116,115,114,1) 71%);
                opacity:${this.opacity};
                z-index:0;
                ${inlineStyles}
            '></div>
            <main style='
                background:${this.color};
                background-size:cover
                ;z-index:-1;
                ${inlineStyles}
            '></main>
        `;
    }
}