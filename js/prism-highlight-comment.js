// prism-highlight-comment.js

document.addEventListener('DOMContentLoaded', function() {
  const codeBlocks = document.querySelectorAll('pre > code[class*="language-"]');

  codeBlocks.forEach(codeElem => {
    const htmlLines = codeElem.innerHTML.split('\n');

    const newLines = htmlLines.map(lineHtml => {

      if (
        lineHtml.includes('/'+'/ *') ||
        lineHtml.includes('#'+' *')  ||
        lineHtml.includes('%'+' *')
      ) {
        return `<span class="hl-star">${lineHtml}</span>`;
      }
      else if (
        lineHtml.includes('/'+'/ $') ||
        lineHtml.includes('#'+' $')  ||
        lineHtml.includes('%'+' $')
      ) {
        return `<span class="hl-dollar">${lineHtml}</span>`;
      }
      else if (
        lineHtml.includes('/'+'/ ^') ||
        lineHtml.includes('#'+' ^')  ||
        lineHtml.includes('%'+' ^')
      ) {
        return `<span class="hl-caret">${lineHtml}</span>`;
      }
      else {
        return lineHtml;
      }
    });

    let result = newLines.join('\n');

    codeElem.innerHTML = result;
  });
});
