<?php
/**
 * @copyright 2022 City of Bloomington, Indiana
 * @license https://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE
 */
declare (strict_types=1);
namespace Web\Views;

use Web\View;

class HelpView extends View
{
    public function render(): string
    {
        return $this->twig->render("{$this->outputFormat}/help.twig");
    }
}
