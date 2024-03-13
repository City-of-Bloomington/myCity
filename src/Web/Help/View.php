<?php
/**
 * @copyright 2024 City of Bloomington, Indiana
 * @license https://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE
 */
declare (strict_types=1);
namespace Web\Help;

class View extends \Web\View
{
    public function render(): string
    {
        return $this->twig->render("{$this->outputFormat}/help.twig");
    }
}
