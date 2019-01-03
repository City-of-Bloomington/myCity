<head>
	<meta http-equiv="x-ua-compatible" content="ie=edge" />
	<meta name="viewport" content="width=device-width, initial-scale=1" />
	<title><?php echo isset($this->title) ? self::escape($this->title) : APPLICATION_NAME; ?></title>
	<link rel="stylesheet" type="text/css" href="<?= BASE_URI ?>/css/screen.css" />
	<?php $this->_include('partials/themeCss.inc') ?>
</head>
