<nav>
  <section>

  </section>
  <section>
  {#if !loggedIn}
  <button on:click={WalletService.login}>Login</button>
    {:else}
    <button on:click={WalletService.logout}>Logout</button>
      
    {/if}
  
  </section>
</nav>


<section class="tamogotchi">
   <section class="info">
    <img src={grickoImage} />
    {#if !loggedIn}
    <section class="panel">
      Welcome to the <b>Gricko</b> game!

      <br />
      <br />
      Click the "Login" button on the top right to sign in and start treating my dog.

  </section>
    {:else}
      {#if !$gricko}
      <section class="panel">
        First time here, eh?
        <br />
        <br />

        Please take care of him!
        <br />
        <br />
        <button on:click={WalletService.create}>Start Game</button>
      </section>
      {:else}
      {#if isDead}
      <section class="panel">
        You betrayed my <b>Gricko</b> and made him <b style="color: red;">die</b>!
        <br />
        <br />

      
        <button on:click={WalletService.create}>Restart Game</button>
      </section>
      {:else}
      <section class="panel">
        {#if $showingConfetti}
            <Confetti x={[-4, 4]} y={[-2, 2]} amount=200 />
        {/if}
        <section class="status-bar">
          <label><span>Food</span></label>
          <figure style="width: {$gricko.calculated_food}%; background: red;"></figure>
        </section>

        <section class="status-bar">
          <label><span>Happiness</span></label>
          <figure style="width: {$gricko.calculated_happiness}%; background: lightgreen;"></figure>
      </section>
      <section class="flex gap-3">
        <button on:click={WalletService.feed}>Feed</button>
        <button on:click={WalletService.play}>Play</button>
      </section>
      </section>
      {/if}

     
      {/if}
    
    {/if}

  
   
   </section>
</section>

<script lang="ts">
 import grickoImage from "$lib/images/r.jpg"
 import WalletService, {session, gricko, showingConfetti} from "../services/Wallet.service";
 import { onMount } from "svelte";
 import { Confetti } from "svelte-confetti";

 onMount(()=>{
  WalletService.init();
 });


 $: loggedIn = !!$session;
 $: isDead = $gricko && ($gricko.calculated_food <= 0 || $gricko.calculated_happiness <=0);

 setInterval(()=>{
  if($gricko){
    WalletService.refreshgricko(false)
  }
  },1000)
 
</script>

<style lang="scss">
    nav{
      position: fixed;
      top: 0;
      left: 0;
      right: 0;
      padding: 20px;
      display: flex;
      justify-content: space-between;
    }
    button{
      background: #333;
      font-size: 13px;
      color: #fff;
      height: 40px;
      padding: 0 20px;
      border-radius: 4px;
      display: flex;
      align-items: center;
      justify-content: center;
      flex: 1;
    }


  .tamogotchi{
    display: flex;
    justify-content: center;
    align-items: center;
    width: 100vw;
    height: 100vh;

    background: linear-gradient(-45deg, #ee7752, #e73c7e, #23a6d5, #23d5ab);
        background-size: 400% 400%;
        animation: gradient 30s ease infinite;
  }

  .info{
    display: flex;
    align-items: center;

    img{
      width: 250px;
      height: 350px;
      display:flex;
      margin-right: 50px;
    
    }

    .panel{
      padding: 20px;
      background: #fff;
      border-radius: 20px;
      width: 300px;
      margin-left: -50px;
      
    }

    .status-bar {
      display:flex;
      align-items: center;
      justify-content: space-between;
      margin-bottom: 10px;
      border: 1px solid #333;
      border-radius: 4px;
      height: 50px;
      position:relative;
      overflow: hidden;
      padding: 2px;

      label{
          position: absolute;
          top: 0;
          bottom: 0;
          left: 0;
          right: 0;
          display: flex;
          align-items: center;
          justify-content: center;

          span{
              font-size: 12px;
              font-weight: bold;
              padding: 3px 6px;
              background: white;
              color: #333;
              border-radius: 4px;

          }

      }
      figure{
        height: 100%;
        border-radius: 4px;
        transition: width 1s ease;
    
      }
    }

  
  }
</style>