	component pcihellocore is
		port (
			green_leds_external_connection_export   : out std_logic_vector(31 downto 0);                    -- export
			hexport2_external_connection_export     : out std_logic_vector(31 downto 0);                    -- export
			hexport_external_connection_export      : out std_logic_vector(31 downto 0);                    -- export
			inport_external_connection_export       : in  std_logic_vector(31 downto 0) := (others => 'X'); -- export
			pcie_hard_ip_0_pcie_rstn_export         : in  std_logic                     := 'X';             -- export
			pcie_hard_ip_0_powerdown_pll_powerdown  : in  std_logic                     := 'X';             -- pll_powerdown
			pcie_hard_ip_0_powerdown_gxb_powerdown  : in  std_logic                     := 'X';             -- gxb_powerdown
			pcie_hard_ip_0_refclk_export            : in  std_logic                     := 'X';             -- export
			pcie_hard_ip_0_rx_in_rx_datain_0        : in  std_logic                     := 'X';             -- rx_datain_0
			pcie_hard_ip_0_tx_out_tx_dataout_0      : out std_logic;                                        -- tx_dataout_0
			push_buttons_external_connection_export : in  std_logic_vector(31 downto 0) := (others => 'X'); -- export
			red_leds_external_connection_export     : out std_logic_vector(31 downto 0)                     -- export
		);
	end component pcihellocore;

	u0 : component pcihellocore
		port map (
			green_leds_external_connection_export   => CONNECTED_TO_green_leds_external_connection_export,   --   green_leds_external_connection.export
			hexport2_external_connection_export     => CONNECTED_TO_hexport2_external_connection_export,     --     hexport2_external_connection.export
			hexport_external_connection_export      => CONNECTED_TO_hexport_external_connection_export,      --      hexport_external_connection.export
			inport_external_connection_export       => CONNECTED_TO_inport_external_connection_export,       --       inport_external_connection.export
			pcie_hard_ip_0_pcie_rstn_export         => CONNECTED_TO_pcie_hard_ip_0_pcie_rstn_export,         --         pcie_hard_ip_0_pcie_rstn.export
			pcie_hard_ip_0_powerdown_pll_powerdown  => CONNECTED_TO_pcie_hard_ip_0_powerdown_pll_powerdown,  --         pcie_hard_ip_0_powerdown.pll_powerdown
			pcie_hard_ip_0_powerdown_gxb_powerdown  => CONNECTED_TO_pcie_hard_ip_0_powerdown_gxb_powerdown,  --                                 .gxb_powerdown
			pcie_hard_ip_0_refclk_export            => CONNECTED_TO_pcie_hard_ip_0_refclk_export,            --            pcie_hard_ip_0_refclk.export
			pcie_hard_ip_0_rx_in_rx_datain_0        => CONNECTED_TO_pcie_hard_ip_0_rx_in_rx_datain_0,        --             pcie_hard_ip_0_rx_in.rx_datain_0
			pcie_hard_ip_0_tx_out_tx_dataout_0      => CONNECTED_TO_pcie_hard_ip_0_tx_out_tx_dataout_0,      --            pcie_hard_ip_0_tx_out.tx_dataout_0
			push_buttons_external_connection_export => CONNECTED_TO_push_buttons_external_connection_export, -- push_buttons_external_connection.export
			red_leds_external_connection_export     => CONNECTED_TO_red_leds_external_connection_export      --     red_leds_external_connection.export
		);

